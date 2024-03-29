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

#include "ops/relu_builder.h"

#include "ops_test.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NeuralNetworkRuntime::Ops;

namespace OHOS {
namespace NeuralNetworkRuntime {
namespace UnitTest {
class ReluBuilderTest : public OpsTest {
public:
    void SetUp() override;
    void TearDown() override;

protected:
    ReluBuilder m_builder;
    std::vector<uint32_t> m_inputs {0};
    std::vector<uint32_t> m_outputs {1};
    std::vector<int32_t> m_dim {1, 5, 1, 1};
};

void ReluBuilderTest::SetUp() {}

void ReluBuilderTest::TearDown() {}

/**
 * @tc.name: relu_build_001
 * @tc.desc: Provide normal input, output, and parameters to verify the normal behavior of the Build function
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_build_001, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_dim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_dim, nullptr);

    OH_NN_ReturnCode ret = m_builder.Build(m_paramsIndex, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_SUCCESS, ret);
}

/**
 * @tc.name: relu_build_002
 * @tc.desc: Call Build func twice to verify the abnormal behavior of the Build function
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_build_002, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_dim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_dim, nullptr);

    EXPECT_EQ(OH_NN_SUCCESS, m_builder.Build(m_paramsIndex, m_inputsIndex, m_outputsIndex, m_allTensors));
    EXPECT_EQ(OH_NN_OPERATION_FORBIDDEN, m_builder.Build(m_paramsIndex, m_inputsIndex, m_outputsIndex, m_allTensors));
}

/**
 * @tc.name: relu_build_003
 * @tc.desc: Provide one more than normal input to verify the abnormal behavior of the Build function
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_build_003, TestSize.Level0)
{
    m_inputs = {0, 1};
    m_outputs = {2};

    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_dim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_dim, nullptr);

    OH_NN_ReturnCode ret = m_builder.Build(m_paramsIndex, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: relu_build_004
 * @tc.desc: Provide one more than normal output to verify the abnormal behavior of the Build function
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_build_004, TestSize.Level0)
{
    m_outputs = {1, 2};

    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_dim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_dim, nullptr);

    OH_NN_ReturnCode ret = m_builder.Build(m_paramsIndex, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: relu_build_005
 * @tc.desc: Verify that the build function return a failed message with null allTensor
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_build_005, TestSize.Level0)
{
    OH_NN_ReturnCode ret = m_builder.Build(m_paramsIndex, m_inputs, m_outputs, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: relu_build_006
 * @tc.desc: Verify that the build function return a failed message without output tensor
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_build_006, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_dim, nullptr);

    OH_NN_ReturnCode ret = m_builder.Build(m_paramsIndex, m_inputsIndex, m_outputs, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: relu_build_007
 * @tc.desc: Verify that the build function return a successful message with a virtual parameter
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_build_007, TestSize.Level0)
{
    std::vector<uint32_t> paramsIndex = {2};
    std::vector<int32_t> paramDim = {};

    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_dim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_dim, nullptr);
    std::shared_ptr<NNTensor> reluTensor = TransToNNTensor(OH_NN_INT32, paramDim, nullptr, OH_NN_TENSOR);
    m_allTensors.emplace_back(reluTensor);

    OH_NN_ReturnCode ret = m_builder.Build(paramsIndex, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: relu_get_primitive_001
 * @tc.desc: Verify the GetPrimitive function return nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_get_primitive_001, TestSize.Level0)
{
    LiteGraphTensorPtr primitive = m_builder.GetPrimitive();
    LiteGraphTensorPtr expectPrimitive = {nullptr, DestroyLiteGraphPrimitive};
    EXPECT_EQ(primitive, expectPrimitive);
}

/**
 * @tc.name: relu_get_primitive_002
 * @tc.desc: Verify the normal params return behavior of the getprimitive function
 * @tc.type: FUNC
 */
HWTEST_F(ReluBuilderTest, relu_get_primitive_002, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_dim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_dim, nullptr);

    EXPECT_EQ(OH_NN_SUCCESS, m_builder.Build(m_paramsIndex, m_inputsIndex, m_outputsIndex, m_allTensors));
    LiteGraphTensorPtr reluPrimitive = m_builder.GetPrimitive();
    LiteGraphTensorPtr expectPrimitive = {nullptr, DestroyLiteGraphPrimitive};
    EXPECT_NE(reluPrimitive, expectPrimitive);

    mindspore::lite::ActivationType activationType = mindspore::lite::ACTIVATION_TYPE_RELU;
    auto returnValue = mindspore::lite::MindIR_Activation_GetActivationType(reluPrimitive.get());
    EXPECT_EQ(returnValue, activationType);
}
} // namespace UnitTest
} // namespace NeuralNetworkRuntime
} // namespace OHOS