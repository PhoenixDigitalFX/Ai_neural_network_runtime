/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "reduceall_builder.h"

#include "ops_registry.h"

namespace OHOS {
namespace NeuralNetworkRuntime {
namespace Ops {
static const int INPUT_NUM = 2;
static const int OUTPUT_NUM = 1;
static const int SCALE_LENGTH = 1;
static const std::string OP_NAME = "ReduceAll";

ReduceAllBuilder::ReduceAllBuilder() {}

ReduceAllBuilder:: ~ReduceAllBuilder() {}

OH_NN_ReturnCode ReduceAllBuilder::SetKeepDims(std::shared_ptr<NNTensor> tensor)
{
    tensor->IdentifyOpParameter();
    if (tensor->GetElementCount() != SCALE_LENGTH) {
        LOGE("[ReduceAll] SetKeepDims failed, the keep_dims dimensions should be scalar.");
        return OH_NN_INVALID_PARAMETER;
    }

    if (tensor->GetDataType() != OH_NN_BOOL) {
        LOGE("[ReduceAll] SetKeepDims failed, the keep_dims should be type OH_NN_BOOL.");
        return OH_NN_INVALID_PARAMETER;
    }

    void* buffer = tensor->GetBuffer();
    if (buffer == nullptr) {
        LOGE("[ReduceAll] SetKeepDims failed, the keep_dims passed buffer is empty.");
        return OH_NN_INVALID_PARAMETER;
    }

    m_keepDims = *(static_cast<bool*>(buffer));
    return OH_NN_SUCCESS;
}

OH_NN_ReturnCode ReduceAllBuilder::Build(const std::vector<uint32_t>& paramsIndex,
                                         const std::vector<uint32_t>& inputsIndex,
                                         const std::vector<uint32_t>& outputsIndex,
                                         const std::vector<std::shared_ptr<NNTensor>>& allTensors)
{
    if (m_isBuild) {
        LOGE("[ReduceAll] Build failed, the ReduceAll operation has been build, cannot build again.");
        return OH_NN_OPERATION_FORBIDDEN;
    }

    OH_NN_ReturnCode returnCode = CheckIOIndex(inputsIndex, outputsIndex, allTensors, INPUT_NUM, OUTPUT_NUM);
    if (returnCode != OH_NN_SUCCESS) {
        LOGE("[ReduceAll] Build failed, passed invalid input or output index of ReduceAll operation index.");
        return returnCode;
    }

    m_inputsIndex = inputsIndex;
    m_outputsIndex = outputsIndex;

    for (uint32_t i : paramsIndex) {
        std::shared_ptr<NNTensor> tensor = allTensors[i];
        switch (tensor->GetType()) {
            case OH_NN_REDUCE_ALL_KEEP_DIMS:
                returnCode = SetKeepDims(tensor);
                break;
            default:
                LOGE("[ReduceAll] Build failed, parameter type is invalid. type=%d", tensor->GetType());
                return OH_NN_INVALID_PARAMETER;
        }

        if (returnCode != OH_NN_SUCCESS) {
            LOGE("[ReduceAll] Build failed, passed invalid param.");
            return returnCode;
        }
    }

    m_name = OP_NAME;
    m_isBuild = true;
    return OH_NN_SUCCESS;
}

LiteGraphPrimitvePtr ReduceAllBuilder::GetPrimitive()
{
    if (!m_isBuild) {
        LOGE("[ReduceAll] GetPrimitive failed, cannot get primitive before call build.");
        return {nullptr, DestroyLiteGraphPrimitive};
    }

    bool reduceToEnd{false};
    float coeff{0.0f};

    void* primitive = mindspore::lite::MindIR_ReduceFusion_CreatePrimitive(m_keepDims, m_mode, reduceToEnd, coeff);
    LiteGraphPrimitvePtr graphPrimitivePtr(primitive, DestroyLiteGraphPrimitive);
    return graphPrimitivePtr;
}

REGISTER_OPS(ReduceAllBuilder, OH_NN_OPS_REDUCE_ALL);
} // namespace Ops
} // namespace NeuralNetworkRuntime
} // namespace OHOS