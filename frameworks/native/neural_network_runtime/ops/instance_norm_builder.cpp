/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "instance_norm_builder.h"

namespace OHOS {
namespace NeuralNetworkRuntime {
namespace Ops {
static const int INPUT_NUM = 3;
static const int OUTPUT_NUM = 1;
static const int SCALAR_LENGTH = 1;
static const std::string OP_NAME = "InstanceNorm";

InstanceNormBuilder::InstanceNormBuilder() {}

InstanceNormBuilder::~InstanceNormBuilder() {}

OH_NN_ReturnCode InstanceNormBuilder::SetEpsilon(std::shared_ptr<NNTensor> tensor)
{
    if (tensor->GetDataType() != OH_NN_FLOAT32) {
        LOGE("[InstanceNorm] The epsilon should be type OH_NN_FLOAT32.");
        return OH_NN_INVALID_PARAMETER;
    }

    if (tensor->GetElementCount() != SCALAR_LENGTH) {
        LOGE("[InstanceNorm] The epsilon should be scalar.");
        return OH_NN_INVALID_PARAMETER;
    }

    void* buffer = tensor->GetBuffer();
    if (buffer == nullptr) {
        LOGE("[InstanceNorm] Tensor buffer is nullptr.");
        return OH_NN_INVALID_PARAMETER;
    }
    m_epsilon = *(static_cast<const float*>(buffer));

    return OH_NN_SUCCESS;
}

OH_NN_ReturnCode InstanceNormBuilder::Build(const std::vector<uint32_t>& paramsIndex,
                                            const std::vector<uint32_t>& inputsIndex,
                                            const std::vector<uint32_t>& outputsIndex,
                                            const std::vector<std::shared_ptr<NNTensor>>& allTensors)
{
    if (m_isBuild) {
        LOGE("[InstanceNorm] Build failed, the InstanceNorm operation has been build. cannot build again.");
        return OH_NN_OPERATION_FORBIDDEN;
    }

    auto ret = CheckIOIndex(inputsIndex, outputsIndex, allTensors, INPUT_NUM, OUTPUT_NUM);
    if (ret != OH_NN_SUCCESS) {
        LOGE("[InstanceNorm] Build failed, passed invalid input or output index.");
        return ret;
    }

    m_inputsIndex = inputsIndex;
    m_outputsIndex = outputsIndex;
    
    OH_NN_ReturnCode returnCode;
    for (int i : paramsIndex) {
        std::shared_ptr<NNTensor> tensor = allTensors[i];
        tensor->IdentifyOpParameter();
        switch (tensor->GetType()) {
            case OH_NN_INSTANCE_NORM_EPSILON:
                returnCode = SetEpsilon(tensor);
                break;
            default:
                LOGE("[InstanceNorm] Build failed, param invalid, type=%d", tensor->GetType());
                return OH_NN_INVALID_PARAMETER;
        }

        if (returnCode != OH_NN_SUCCESS) {
            LOGE("[InstanceNorm] Build failed, passed invalid param.");
            return returnCode;
        }
    }

    m_name = OP_NAME;
    m_isBuild = true;
    return OH_NN_SUCCESS;
}

LiteGraphPrimitvePtr InstanceNormBuilder::GetPrimitive()
{
    if (!m_isBuild) {
        LOGE("[InstanceNorm] GetPrimitive failed, cannot get primitive before call build.");
        return {nullptr, DestroyLiteGraphPrimitive};
    }

    void* primitive = mindspore::lite::MindIR_InstanceNorm_CreatePrimitive(m_epsilon);
    LiteGraphPrimitvePtr graphPrimitivePtr(primitive, DestroyLiteGraphPrimitive) ;
    return graphPrimitivePtr;
}

REGISTER_OPS(InstanceNormBuilder, OH_NN_OPS_INSTANCE_NORM);
} // namespace Ops
} // namespace NeuralNetworkRuntime
} // namespace OHOS
