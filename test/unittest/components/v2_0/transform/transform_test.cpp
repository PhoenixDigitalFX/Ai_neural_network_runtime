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

#include <gtest/gtest.h>

#include "transform.h"
#include "memory_manager.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::NeuralNetworkRuntime;
namespace OHOS {
namespace NeuralNetworkRuntime {
namespace UnitTest {
class TransformTest : public testing::Test {
public:
    TransformTest() = default;
    ~TransformTest() = default;
};

/**
 * @tc.name: transform_gettypesize_001
 * @tc.desc: Verify the TransIOTensor function return 1.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_gettypesize_001, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_BOOL;
    uint32_t result = GetTypeSize(dataType);
    EXPECT_EQ(static_cast<uint32_t>(1), result);
}

/**
 * @tc.name: transform_gettypesize_002
 * @tc.desc: Verify the TransIOTensor function return 2.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_gettypesize_002, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_INT16;
    uint32_t result = GetTypeSize(dataType);
    EXPECT_EQ(static_cast<uint32_t>(2), result);
}

/**
 * @tc.name: transform_gettypesize_003
 * @tc.desc: Verify the TransIOTensor function return 4.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_gettypesize_003, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_INT32;
    uint32_t result = GetTypeSize(dataType);
    EXPECT_EQ(static_cast<uint32_t>(4), result);
}

/**
 * @tc.name: transform_gettypesize_004
 * @tc.desc: Verify the TransIOTensor function return 8.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_gettypesize_004, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_INT64;
    uint32_t result = GetTypeSize(dataType);
    EXPECT_EQ(static_cast<uint32_t>(8), result);
}

/**
 * @tc.name: transform_gettypesize_005
 * @tc.desc: Verify the TransIOTensor function return 0.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_gettypesize_005, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_UNKNOWN;
    uint32_t result = GetTypeSize(dataType);
    EXPECT_EQ(static_cast<uint32_t>(0), result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_001
 * @tc.desc: Verify the TransIOTensor function return DATA_TYPE_BOOL.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_001, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_BOOL;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_BOOL, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_002
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_INT8.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_002, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_INT8;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_INT8, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_003
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_INT16.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_003, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_INT16;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_INT16, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_004
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_INT32.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_004, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_INT32;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_INT32, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_005
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_INT64.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_005, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_INT64;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_INT64, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_006
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_UINT8.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_006, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_UINT8;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_UINT8, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_007
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_UINT16.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_007, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_UINT16;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_UINT16, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_008
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_UINT32.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_008, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_UINT32;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_UINT32, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_009
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_UINT64.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_009, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_UINT64;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_UINT64, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_010
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_FLOAT16.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_010, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_FLOAT16;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_FLOAT16, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_011
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_FLOAT32.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_011, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_FLOAT32;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_FLOAT32, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_012
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_UNKNOWN.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_012, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_UNKNOWN;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_UNKNOWN, result);
}

/**
 * @tc.name: transform_nntoms_transformdatatype_013
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_FLOAT64
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformdatatype_013, TestSize.Level0)
{
    OH_NN_DataType dataType = OH_NN_FLOAT64;
    mindspore::lite::DataType result = NNToMS::TransformDataType(dataType);
    EXPECT_EQ(mindspore::lite::DATA_TYPE_FLOAT64, result);
}

/**
 * @tc.name: transform_nntoms_transformformat_001
 * @tc.desc: Verify the TransFormat function return FORMAT_NCHW.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformformat_001, TestSize.Level0)
{
    OH_NN_Format format = OH_NN_FORMAT_NCHW;
    mindspore::lite::Format result = NNToMS::TransformFormat(format);
    EXPECT_EQ(mindspore::lite::FORMAT_NCHW, result);
}

/**
 * @tc.name: transform_nntoms_transformformat_002
 * @tc.desc: Verify the TransFormat function return FORMAT_NHWC.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformformat_002, TestSize.Level0)
{
    OH_NN_Format format = OH_NN_FORMAT_NHWC;
    mindspore::lite::Format result = NNToMS::TransformFormat(format);
    EXPECT_EQ(mindspore::lite::FORMAT_NHWC, result);
}

/**
 * @tc.name: transform_nntoms_transformformat_003
 * @tc.desc: Verify the TransFormat function return FORMAT_NHWC.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformformat_003, TestSize.Level0)
{
    OH_NN_Format format = OH_NN_FORMAT_NONE;
    mindspore::lite::Format result = NNToMS::TransformFormat(format);
    EXPECT_EQ(mindspore::lite::FORMAT_NHWC, result);
}

/**
 * @tc.name: transform_nntoms_transformfusiontype_001
 * @tc.desc: Verify the TransFormat function return ACTIVATION_TYPE_NO_ACTIVATION.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformfusiontype_001, TestSize.Level0)
{
    OH_NN_FuseType type = OH_NN_FUSED_NONE;
    mindspore::lite::ActivationType result = NNToMS::TransfromFusionType(type);
    EXPECT_EQ(mindspore::lite::ACTIVATION_TYPE_NO_ACTIVATION, result);
}

/**
 * @tc.name: transform_nntoms_transformfusiontype_002
 * @tc.desc: Verify the TransFormat function return ACTIVATION_TYPE_RELU.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformfusiontype_002, TestSize.Level0)
{
    OH_NN_FuseType type = OH_NN_FUSED_RELU;
    mindspore::lite::ActivationType result = NNToMS::TransfromFusionType(type);
    EXPECT_EQ(mindspore::lite::ACTIVATION_TYPE_RELU, result);
}

/**
 * @tc.name: transform_nntoms_transformfusiontype_003
 * @tc.desc: Verify the TransFormat function return ACTIVATION_TYPE_RELU6.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformfusiontype_003, TestSize.Level0)
{
    OH_NN_FuseType type = OH_NN_FUSED_RELU6;
    mindspore::lite::ActivationType result = NNToMS::TransfromFusionType(type);
    EXPECT_EQ(mindspore::lite::ACTIVATION_TYPE_RELU6, result);
}

/**
 * @tc.name: transform_nntoms_transformquanttype_001
 * @tc.desc: Verify the TransFormat function return QUANT_TYPE_NONE.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformquanttype_001, TestSize.Level0)
{
    OHOS::NeuralNetworkRuntime::Ops::OpsQuantType type = OHOS::NeuralNetworkRuntime::Ops::OpsQuantType::QUANT_NONE;
    mindspore::lite::QuantType result = NNToMS::TransformQuantType(type);
    EXPECT_EQ(mindspore::lite::QUANT_TYPE_NONE, result);
}

/**
 * @tc.name: transform_nntoms_transformquanttype_002
 * @tc.desc: Verify the TransFormat function return QUANT_TYPE_ALL.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_nntoms_transformquanttype_002, TestSize.Level0)
{
    OHOS::NeuralNetworkRuntime::Ops::OpsQuantType type = OHOS::NeuralNetworkRuntime::Ops::OpsQuantType::QUANT_ALL;
    mindspore::lite::QuantType result = NNToMS::TransformQuantType(type);
    EXPECT_EQ(mindspore::lite::QUANT_TYPE_ALL, result);
}


/**
 * @tc.name: transform_mstonn_transformdatatype_001
 * @tc.desc: Verify the TransIOTensor function return OH_NN_BOOL.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_001, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_BOOL;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_BOOL, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_002
 * @tc.desc: Verify the TransDataType function return OH_NN_INT8.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_002, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_INT8;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_INT8, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_003
 * @tc.desc: Verify the TransDataType function return OH_NN_INT16.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_003, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_INT16;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_INT16, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_004
 * @tc.desc: Verify the TransDataType function return OH_NN_INT32.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_004, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_INT32;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_INT32, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_005
 * @tc.desc: Verify the TransDataType function return OH_NN_INT64.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_005, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_INT64;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_INT64, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_006
 * @tc.desc: Verify the TransDataType function return OH_NN_UINT8.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_006, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_UINT8;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_UINT8, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_007
 * @tc.desc: Verify the TransDataType function return OH_NN_UINT16.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_007, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_UINT16;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_UINT16, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_008
 * @tc.desc: Verify the TransDataType function return OH_NN_UINT32.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_008, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_UINT32;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_UINT32, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_009
 * @tc.desc: Verify the TransDataType function return OH_NN_UINT64.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_009, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_UINT64;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_UINT64, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_010
 * @tc.desc: Verify the TransDataType function return OH_NN_FLOAT16
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_010, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_FLOAT16;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_FLOAT16, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_011
 * @tc.desc: Verify the TransDataType function return OH_NN_FLOAT32.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_011, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_FLOAT32;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_FLOAT32, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_012
 * @tc.desc: Verify the TransDataType function return OH_NN_UNKNOWN.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_012, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_UNKNOWN;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_UNKNOWN, result);
}

/**
 * @tc.name: transform_mstonn_transformdatatype_013
 * @tc.desc: Verify the TransDataType function return DATA_TYPE_FLOAT64
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformdatatype_013, TestSize.Level0)
{
    mindspore::lite::DataType dataType = mindspore::lite::DATA_TYPE_FLOAT64;
    OH_NN_DataType result = MSToNN::TransformDataType(dataType);
    EXPECT_EQ(OH_NN_FLOAT64, result);
}

/**
 * @tc.name: transform_mstonn_transformquantparams_001
 * @tc.desc: Verify the TransformQuantParams function.
 * @tc.type: FUNC
 */
HWTEST_F(TransformTest, transform_mstonn_transformquantparams_001, TestSize.Level0)
{
    std::vector<mindspore::lite::QuantParam> msQuantParams = {{1, 1.0, 8}};
    std::vector<QuantParam> result = MSToNN::TransformQuantParams(msQuantParams);
    EXPECT_EQ(msQuantParams.size(), result.size());
}
} // namespace UnitTest
} // namespace NeuralNetworkRuntime
} // namespace OHOS
