/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "ops/sparse_to_dense_builder.h"

#include "ops_test.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NeuralNetworkRuntime::Ops;

namespace OHOS {
namespace NeuralNetworkRuntime {
namespace UnitTest {
class SparseToDenseBuilderTest : public OpsTest {
public:
    void SetUp() override;
    void TearDown() override;

protected:
    void SetInputTensor();
    void SetOutputTensor();

protected:
    SparseToDenseBuilder m_builder;
    std::vector<uint32_t> m_inputs {0, 1, 2};
    std::vector<uint32_t> m_outputs {3};
    std::vector<uint32_t> m_params {};
    std::vector<int32_t> m_indicesDim {2, 2};
    std::vector<int32_t> m_valueDim {2};
    std::vector<int32_t> m_sparseShapeDim {2};
    std::vector<int32_t> m_outputDim {2, 3};
};

void SparseToDenseBuilderTest::SetUp() {}

void SparseToDenseBuilderTest::TearDown() {}

void SparseToDenseBuilderTest::SetInputTensor()
{
    m_inputsIndex = m_inputs;
    std::shared_ptr<NNTensor> indicesTensor;
    indicesTensor = TransToNNTensor(OH_NN_FLOAT32, m_indicesDim, nullptr, OH_NN_TENSOR);
    m_allTensors.emplace_back(indicesTensor);

    std::shared_ptr<NNTensor> valueTensor;
    valueTensor = TransToNNTensor(OH_NN_FLOAT32, m_valueDim, nullptr, OH_NN_TENSOR);
    m_allTensors.emplace_back(valueTensor);

    std::shared_ptr<NNTensor> sparseShapeTensor;
    sparseShapeTensor = TransToNNTensor(OH_NN_FLOAT32, m_sparseShapeDim, nullptr, OH_NN_TENSOR);
    m_allTensors.emplace_back(sparseShapeTensor);
}

/**
 * @tc.name: SparseToDense_build_001
 * @tc.desc: Verify that the build function returns a successful message.
 * @tc.type: FUNC
 */
HWTEST_F(SparseToDenseBuilderTest, SparseToDense_build_001, TestSize.Level1)
{
    SetInputTensor();
    SaveOutputTensor(m_outputs, OH_NN_INT32, m_outputDim, nullptr);

    OH_NN_ReturnCode ret = m_builder.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_SUCCESS, ret);
}

/**
 * @tc.name: SparseToDense_build_002
 * @tc.desc: Verify that the build function returns a failed message with true m_isBuild.
 * @tc.type: FUNC
 */
HWTEST_F(SparseToDenseBuilderTest, SparseToDense_build_002, TestSize.Level1)
{
    SetInputTensor();
    SaveOutputTensor(m_outputs, OH_NN_INT32, m_outputDim, nullptr);

    EXPECT_EQ(OH_NN_SUCCESS, m_builder.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors));
    OH_NN_ReturnCode ret = m_builder.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_OPERATION_FORBIDDEN, ret);
}

/**
 * @tc.name: SparseToDense_build_003
 * @tc.desc: Verify that the build function returns a failed message with invalided input.
 * @tc.type: FUNC
 */
HWTEST_F(SparseToDenseBuilderTest, SparseToDense_build_003, TestSize.Level1)
{
    m_inputs = {0, 1, 2, 3};
    m_outputs = {4};

    SetInputTensor();
    SaveOutputTensor(m_outputs, OH_NN_INT32, m_outputDim, nullptr);

    OH_NN_ReturnCode ret = m_builder.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: SparseToDense_build_004
 * @tc.desc: Verify that the build function returns a failed message with invalided output.
 * @tc.type: FUNC
 */
HWTEST_F(SparseToDenseBuilderTest, SparseToDense_build_004, TestSize.Level1)
{
    m_outputs = {3, 4};

    SetInputTensor();
    SaveOutputTensor(m_outputs, OH_NN_INT32, m_outputDim, nullptr);

    OH_NN_ReturnCode ret = m_builder.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: SparseToDense_build_005
 * @tc.desc: Verify that the build function returns a failed message with empty allTensor.
 * @tc.type: FUNC
 */
HWTEST_F(SparseToDenseBuilderTest, SparseToDense_build_005, TestSize.Level1)
{
    OH_NN_ReturnCode ret = m_builder.Build(m_params, m_inputs, m_outputs, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: SparseToDense_build_006
 * @tc.desc: Verify that the build function returns a failed message without output tensor.
 * @tc.type: FUNC
 */
HWTEST_F(SparseToDenseBuilderTest, SparseToDense_build_006, TestSize.Level1)
{
    SetInputTensor();

    OH_NN_ReturnCode ret = m_builder.Build(m_params, m_inputsIndex, m_outputs, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: SparseToDense_getprimitive_001
 * @tc.desc: Verify that the getPrimitive function returns a successful message.
 * @tc.type: FUNC
 */
HWTEST_F(SparseToDenseBuilderTest, SparseToDense_getprimitive_001, TestSize.Level1)
{
    SetInputTensor();
    SaveOutputTensor(m_outputs, OH_NN_INT32, m_outputDim, nullptr);

    EXPECT_EQ(OH_NN_SUCCESS, m_builder.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors));
    LiteGraphPrimitvePtr primitive = m_builder.GetPrimitive();
    LiteGraphPrimitvePtr expectPrimitive(nullptr, DestroyLiteGraphPrimitive);
    EXPECT_NE(expectPrimitive, primitive);
}

/**
 * @tc.name: SparseToDense_getprimitive_002
 * @tc.desc: Verify that the getPrimitive function returns a failed message without build.
 * @tc.type: FUNC
 */
HWTEST_F(SparseToDenseBuilderTest, SparseToDense_getprimitive_002, TestSize.Level1)
{
    LiteGraphPrimitvePtr primitive = m_builder.GetPrimitive();
    LiteGraphPrimitvePtr expectPrimitive(nullptr, DestroyLiteGraphPrimitive);
    EXPECT_EQ(expectPrimitive, primitive);
}
}
}
}