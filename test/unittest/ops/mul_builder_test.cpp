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

#include "ops/mul_builder.h"

#include "ops_test.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NeuralNetworkRuntime::Ops;

namespace OHOS {
namespace NeuralNetworkRuntime {
namespace UnitTest {
class MulBuilderTest : public OpsTest {
public:
    void SetUp() override;
    void TearDown() override;

protected:
    void SaveParamsTensor(OH_NN_DataType dataType,
        const std::vector<int32_t> &dim,  const OH_NN_QuantParam* quantParam, OH_NN_TensorType type);

protected:
    MulBuilder m_mul;
    std::vector<uint32_t> m_inputs {0, 1};
    std::vector<uint32_t> m_outputs {2};
    std::vector<uint32_t> m_params {3};
    std::vector<int32_t> m_inputDim {1, 2, 2, 1};
    std::vector<int32_t> m_outputDim {1, 2, 2, 1};
    std::vector<int32_t> m_paramDim {};
};

void MulBuilderTest::SetUp() {}

void MulBuilderTest::TearDown() {}

void MulBuilderTest::SaveParamsTensor(OH_NN_DataType dataType,
    const std::vector<int32_t> &dim, const OH_NN_QuantParam* quantParam, OH_NN_TensorType type)
{
    std::shared_ptr<NNTensor> activationTensor = TransToNNTensor(dataType, dim, quantParam, type);
    int8_t* activationValue = new (std::nothrow) int8_t(0);
    EXPECT_NE(nullptr, activationValue);
    activationTensor->SetBuffer(activationValue, sizeof(int8_t));
    m_allTensors.emplace_back(activationTensor);
}

/**
 * @tc.name: mul_build_001
 * @tc.desc: Verify that the build function returns a successful message.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_001, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);
    SaveParamsTensor(OH_NN_INT8, m_paramDim, nullptr, OH_NN_MUL_ACTIVATION_TYPE);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_SUCCESS, ret);
}

/**
 * @tc.name: mul_build_002
 * @tc.desc: Verify that the build function returns a failed message with true m_isBuild.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_002, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);
    SaveParamsTensor(OH_NN_INT8, m_paramDim, nullptr, OH_NN_MUL_ACTIVATION_TYPE);

    EXPECT_EQ(OH_NN_SUCCESS, m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors));
    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_OPERATION_FORBIDDEN, ret);
}

/**
 * @tc.name: mul_build_003
 * @tc.desc: Verify that the build function returns a failed message with invalided input.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_003, TestSize.Level0)
{
    m_inputs = {0, 1, 2};
    m_outputs = {3};
    m_params = {4};

    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);
    SaveParamsTensor(OH_NN_INT8, m_paramDim, nullptr, OH_NN_MUL_ACTIVATION_TYPE);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: mul_build_004
 * @tc.desc: Verify that the build function returns a failed message with invalided output.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_004, TestSize.Level0)
{
    m_outputs = {2, 3};
    m_params = {4};

    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);
    SaveParamsTensor(OH_NN_INT8, m_paramDim, nullptr, OH_NN_MUL_ACTIVATION_TYPE);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: mul_build_005
 * @tc.desc: Verify that the build function returns a failed message with empty allTensor.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_005, TestSize.Level0)
{
    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputs, m_outputs, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: mul_build_006
 * @tc.desc: Verify that the build function returns a failed message without output tensor.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_006, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputs, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: mul_build_007
 * @tc.desc: Verify that the build function returns a failed message with invalid activation's dataType.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_007, TestSize.Level0)
{
    m_params = {3};
    std::vector<int32_t> m_paramDim = {};

    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);

    std::shared_ptr<NNTensor> activationTensor = TransToNNTensor(OH_NN_FLOAT32, m_paramDim,
        nullptr, OH_NN_MUL_ACTIVATION_TYPE);
    float activationValue = 1e-7;
    activationTensor->SetBuffer(&activationValue, sizeof(activationValue));
    m_allTensors.emplace_back(activationTensor);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
    activationTensor->SetBuffer(nullptr, 0);
}

/**
 * @tc.name: mul_build_008
 * @tc.desc: Verify that the build function returns a failed message with invalid activation's dimension.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_008, TestSize.Level0)
{
    m_paramDim = {2};

    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);

    std::shared_ptr<NNTensor> activationTensor = TransToNNTensor(OH_NN_INT8, m_paramDim,
        nullptr, OH_NN_MUL_ACTIVATION_TYPE);
    int8_t activationValue[2] = {0, 1};
    activationTensor->SetBuffer(activationValue, 2 * sizeof(int8_t));
    m_allTensors.emplace_back(activationTensor);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
    activationTensor->SetBuffer(nullptr, 0);
}

/**
 * @tc.name: mul_build_009
 * @tc.desc: Verify that the build function returns a failed message with invalid activation's data.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_009, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);

    std::shared_ptr<NNTensor> activationTensor = TransToNNTensor(OH_NN_INT8, m_paramDim,
        nullptr, OH_NN_MUL_ACTIVATION_TYPE);
    int8_t activationValue = -1;
    activationTensor->SetBuffer(&activationValue, sizeof(activationValue));
    m_allTensors.emplace_back(activationTensor);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
    activationTensor->SetBuffer(nullptr, 0);
}

/**
 * @tc.name: mul_build_010
 * @tc.desc: Verify that the build function returns a failed message with passing invalid param.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_010, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);
    SaveParamsTensor(OH_NN_INT8, m_paramDim, nullptr, OH_NN_MATMUL_ACTIVATION_TYPE);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: mul_build_011
 * @tc.desc: Verify that the build function returns a failed message without set buffer for activation.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_build_011, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);

    std::shared_ptr<NNTensor> activationTensor = TransToNNTensor(OH_NN_INT8, m_paramDim,
        nullptr, OH_NN_MUL_ACTIVATION_TYPE);
    m_allTensors.emplace_back(activationTensor);

    OH_NN_ReturnCode ret = m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors);
    EXPECT_EQ(OH_NN_INVALID_PARAMETER, ret);
}

/**
 * @tc.name: mul_getprimitive_001
 * @tc.desc: Verify that the getPrimitive function returns a successful message
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_getprimitive_001, TestSize.Level0)
{
    SaveInputTensor(m_inputs, OH_NN_FLOAT32, m_inputDim, nullptr);
    SaveOutputTensor(m_outputs, OH_NN_FLOAT32, m_outputDim, nullptr);
    SaveParamsTensor(OH_NN_INT8, m_paramDim, nullptr, OH_NN_MUL_ACTIVATION_TYPE);

    int8_t activationValue = 0;
    EXPECT_EQ(OH_NN_SUCCESS, m_mul.Build(m_params, m_inputsIndex, m_outputsIndex, m_allTensors));
    LiteGraphPrimitvePtr primitive = m_mul.GetPrimitive();
    LiteGraphPrimitvePtr expectPrimitive(nullptr, DestroyLiteGraphPrimitive);
    EXPECT_NE(expectPrimitive, primitive);

    auto returnValue = mindspore::lite::MindIR_MulFusion_GetActivationType(primitive.get());
    EXPECT_EQ(returnValue, activationValue);
}

/**
 * @tc.name: mul_getprimitive_002
 * @tc.desc: Verify that the getPrimitive function returns a failed message without build.
 * @tc.type: FUNC
 */
HWTEST_F(MulBuilderTest, mul_getprimitive_002, TestSize.Level0)
{
    MulBuilder mul;
    LiteGraphPrimitvePtr primitive = m_mul.GetPrimitive();
    LiteGraphPrimitvePtr expectPrimitive(nullptr, DestroyLiteGraphPrimitive);
    EXPECT_EQ(expectPrimitive, primitive);
}
}
}
}