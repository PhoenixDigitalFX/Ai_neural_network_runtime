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

#include "lite_graph_to_hdi_model_v2_1.h"
#include <vector>
#include <algorithm>
#include <sys/mman.h>
#include "common/log.h"
#include "message_parcel.h"
#include "nnrt/v2_1/nnrt_types.h"
#include "nnrt/v2_1/node_attr_types.h"
#include "securec.h"

using namespace OHOS::HDI::Nnrt::V2_1;
typedef void *PrimitivePtr;
typedef void *TensorPtr;
namespace OHOS {
namespace NeuralNetworkRuntime {
namespace NNRt_V2_1 {
std::vector<int8_t> ConvertActivation(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertActivation v2_1 failed, primitive is nullptr.");
        return {};
    }

    Activation activation{};
    activation.activationType = static_cast<HDI::Nnrt::V2_1::ActivationType>(
        mindspore::lite::MindIR_Activation_GetActivationType(primitive));
    activation.alpha = mindspore::lite::MindIR_Activation_GetAlpha(primitive);
    activation.minVal = mindspore::lite::MindIR_Activation_GetMinVal(primitive);
    activation.maxVal = mindspore::lite::MindIR_Activation_GetMaxVal(primitive);
    activation.approximate = mindspore::lite::MindIR_Activation_GetApproximate(primitive);

    OHOS::MessageParcel data;
    (void)ActivationBlockMarshalling(data, activation);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertAddFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertAddFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    AddFusion add_fusion{};
    add_fusion.activationType = static_cast<HDI::Nnrt::V2_1::ActivationType>(
        mindspore::lite::MindIR_Activation_GetActivationType(primitive));

    OHOS::MessageParcel data;
    (void)AddFusionBlockMarshalling(data, add_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertAll(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertAll v2_1 failed, primitive is nullptr.");
        return {};
    }

    All all{};
    all.keepDims = mindspore::lite::MindIR_All_GetKeepDims(primitive);

    OHOS::MessageParcel data;
    (void)AllBlockMarshalling(data, all);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertArgMaxFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertArgMaxFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    ArgMaxFusion arg_max_fusion{};
    arg_max_fusion.axis = mindspore::lite::MindIR_ArgMaxFusion_GetAxis(primitive);
    arg_max_fusion.topK = mindspore::lite::MindIR_ArgMaxFusion_GetTopK(primitive);
    arg_max_fusion.keepDims = mindspore::lite::MindIR_ArgMaxFusion_GetKeepDims(primitive);
    arg_max_fusion.outMaxValue = mindspore::lite::MindIR_ArgMaxFusion_GetOutMaxValue(primitive);

    OHOS::MessageParcel data;
    (void)ArgMaxFusionBlockMarshalling(data, arg_max_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertAssert(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertAssert v2_1 failed, primitive is nullptr.");
        return {};
    }

    Assert assert{};
    assert.summarize = mindspore::lite::MindIR_Assert_GetSummarize(primitive);

    OHOS::MessageParcel data;
    (void)AssertBlockMarshalling(data, assert);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertAvgPoolFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertAvgPoolFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    AvgPoolFusion avg_pool_fusion{};
    avg_pool_fusion.kernelSize = mindspore::lite::MindIR_AvgPoolFusion_GetKernelSize(primitive);
    avg_pool_fusion.strides = mindspore::lite::MindIR_AvgPoolFusion_GetStrides(primitive);
    avg_pool_fusion.pad = mindspore::lite::MindIR_AvgPoolFusion_GetPad(primitive);
    avg_pool_fusion.padMode = static_cast<PadMode>(mindspore::lite::MindIR_AvgPoolFusion_GetPadMode(primitive));
    avg_pool_fusion.roundMode = static_cast<RoundMode>(mindspore::lite::MindIR_AvgPoolFusion_GetRoundMode(primitive));
    avg_pool_fusion.format = static_cast<Format>(mindspore::lite::MindIR_AvgPoolFusion_GetFormat(primitive));
    avg_pool_fusion.global = mindspore::lite::MindIR_AvgPoolFusion_GetGlobal(primitive);
    avg_pool_fusion.activationType =
        static_cast<ActivationType>(mindspore::lite::MindIR_AvgPoolFusion_GetActivationType(primitive));

    OHOS::MessageParcel data;
    (void)AvgPoolFusionBlockMarshalling(data, avg_pool_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertBatchToSpaceND(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertBatchToSpaceND v2_1 failed, primitive is nullptr.");
        return {};
    }

    BatchToSpaceND batch_to_space_n_d{};
    batch_to_space_n_d.blockShape = mindspore::lite::MindIR_BatchToSpaceND_GetBlockShape(primitive);
    batch_to_space_n_d.crops = mindspore::lite::MindIR_BatchToSpaceND_GetCrops(primitive);

    OHOS::MessageParcel data;
    (void)BatchToSpaceNDBlockMarshalling(data, batch_to_space_n_d);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertBiasAdd(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertBiasAdd v2_1 failed, primitive is nullptr.");
        return {};
    }

    BiasAdd bias_add{};
    OHOS::MessageParcel data;
    (void)BiasAddBlockMarshalling(data, bias_add);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertBroadcastTo(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertBroadcastTo v2_1 failed, primitive is nullptr.");
        return {};
    }

    BroadcastTo broadcastTo{};
    broadcastTo.shape = mindspore::lite::MindIR_BroadcastTo_GetShape(primitive);

    OHOS::MessageParcel data;
    (void)BroadcastToBlockMarshalling(data, broadcastTo);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertCast(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertCast v2_1 failed, primitive is nullptr.");
        return {};
    }

    Cast cast{};
    OHOS::MessageParcel data;
    (void)CastBlockMarshalling(data, cast);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertClip(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertClip v2_1 failed, primitive is nullptr.");
        return {};
    }

    Clip clip{};
    clip.max = mindspore::lite::MindIR_Clip_GetMax(primitive);
    clip.min = mindspore::lite::MindIR_Clip_GetMin(primitive);

    OHOS::MessageParcel data;
    (void)ClipBlockMarshalling(data, clip);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertConcat(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertConcat v2_1 failed, primitive is nullptr.");
        return {};
    }

    Concat concat{};
    concat.axis = mindspore::lite::MindIR_Concat_GetAxis(primitive);
    OHOS::MessageParcel data;
    (void)ConcatBlockMarshalling(data, concat);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertConv2DFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertConv2DFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    Conv2DFusion conv2_d_fusion{};
    conv2_d_fusion.kernelSize = mindspore::lite::MindIR_Conv2DFusion_GetKernelSize(primitive);
    conv2_d_fusion.stride = mindspore::lite::MindIR_Conv2DFusion_GetStride(primitive);
    conv2_d_fusion.dilation = mindspore::lite::MindIR_Conv2DFusion_GetDilation(primitive);
    conv2_d_fusion.padMode = static_cast<PadMode>(mindspore::lite::MindIR_Conv2DFusion_GetPadMode(primitive));
    conv2_d_fusion.padList = mindspore::lite::MindIR_Conv2DFusion_GetPadList(primitive);
    conv2_d_fusion.group = mindspore::lite::MindIR_Conv2DFusion_GetGroup(primitive);
    conv2_d_fusion.inChannel = mindspore::lite::MindIR_Conv2DFusion_GetInChannel(primitive);
    conv2_d_fusion.outChannel = mindspore::lite::MindIR_Conv2DFusion_GetOutChannel(primitive);
    conv2_d_fusion.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_Conv2DFusion_GetActivationType(primitive));

    OHOS::MessageParcel data;
    (void)Conv2DFusionBlockMarshalling(data, conv2_d_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertConv2dTransposeFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertConv2dTransposeFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    Conv2dTransposeFusion conv2d_transpose_fusion{};
    conv2d_transpose_fusion.kernelSize = mindspore::lite::MindIR_Conv2dTransposeFusion_GetKernelSize(primitive);
    conv2d_transpose_fusion.stride = mindspore::lite::MindIR_Conv2dTransposeFusion_GetStride(primitive);
    conv2d_transpose_fusion.dilation = mindspore::lite::MindIR_Conv2dTransposeFusion_GetDilation(primitive);
    conv2d_transpose_fusion.padMode = static_cast<PadMode>(
        mindspore::lite::MindIR_Conv2dTransposeFusion_GetPadMode(primitive));
    conv2d_transpose_fusion.padList = mindspore::lite::MindIR_Conv2dTransposeFusion_GetPadList(primitive);
    conv2d_transpose_fusion.group = mindspore::lite::MindIR_Conv2dTransposeFusion_GetGroup(primitive);
    conv2d_transpose_fusion.inChannel = mindspore::lite::MindIR_Conv2dTransposeFusion_GetInChannel(primitive);
    conv2d_transpose_fusion.outChannel = mindspore::lite::MindIR_Conv2dTransposeFusion_GetOutChannel(primitive);
    conv2d_transpose_fusion.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_Conv2dTransposeFusion_GetActivationType(primitive));
    conv2d_transpose_fusion.outputPaddings = mindspore::lite::MindIR_Conv2dTransposeFusion_GetOutputPaddings(primitive);

    OHOS::MessageParcel data;
    (void)Conv2dTransposeFusionBlockMarshalling(data, conv2d_transpose_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertCos(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertCos v2_1 failed, primitive is nullptr.");
        return {};
    }

    Cos cos{};

    OHOS::MessageParcel data;
    (void)CosBlockMarshalling(data, cos);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertConstantOfShape(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertConstantOfShape v2_1 failed, primitive is nullptr.");
        return {};
    }

    ConstantOfShape constantOfShape{};
    constantOfShape.data_type = mindspore::lite::MindIR_ConstantOfShape_GetDataType(primitive);
    constantOfShape.value = mindspore::lite::MindIR_ConstantOfShape_GetValue(primitive);

    OHOS::MessageParcel data;
    (void)ConstantOfShapeBlockMarshalling(data, constantOfShape);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertDepthToSpace(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertDepthToSpace v2_1 failed, primitive is nullptr.");
        return {};
    }

    DepthToSpace depthToSpace{};
    depthToSpace.block_size = mindspore::lite::MindIR_DepthToSpace_GetBlockSize(primitive);
    depthToSpace.format = static_cast<Format>(
        mindspore::lite::MindIR_DepthToSpace_GetFormat(primitive));
    depthToSpace.mode = mindspore::lite::MindIR_DepthToSpace_GetMode(primitive);
    
    OHOS::MessageParcel data;
    (void)DepthToSpaceBlockMarshalling(data, depthToSpace);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertDivFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertDivFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    DivFusion div_fusion{};
    div_fusion.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_DivFusion_GetActivationType(primitive));
    OHOS::MessageParcel data;
    (void)DivFusionBlockMarshalling(data, div_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertEltwise(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertEltwise v2_1 failed, primitive is nullptr.");
        return {};
    }

    Eltwise eltwise{};
    eltwise.mode = static_cast<EltwiseMode>(mindspore::lite::MindIR_Eltwise_GetMode(primitive));
    OHOS::MessageParcel data;
    (void)EltwiseBlockMarshalling(data, eltwise);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertEqual(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertEqual v2_1 failed, primitive is nullptr.");
        return {};
    }

    Equal equal{};
    OHOS::MessageParcel data;
    (void)EqualBlockMarshalling(data, equal);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertExpFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertExp v2_1 failed, primitive is nullptr.");
        return {};
    }

    ExpFusion exp{};
    exp.base = mindspore::lite::MindIR_ExpFusion_GetBase(primitive);
    exp.scale = mindspore::lite::MindIR_ExpFusion_GetScale(primitive);
    exp.shift = mindspore::lite::MindIR_ExpFusion_GetShift(primitive);

    OHOS::MessageParcel data;
    (void)ExpFusionBlockMarshalling(data, exp);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertExpandDims(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertExpandDims v2_1 failed, primitive is nullptr.");
        return {};
    }

    ExpandDims expand_dims{};
    OHOS::MessageParcel data;
    (void)ExpandDimsBlockMarshalling(data, expand_dims);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertFlatten(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertFlatten v2_1 failed, primitive is nullptr.");
        return {};
    }

    Flatten faltten{};
    faltten.axis = mindspore::lite::MindIR_Flatten_GetAxis(primitive);

    OHOS::MessageParcel data;
    (void)FlattenBlockMarshalling(data, faltten);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertFill(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertFill v2_1 failed, primitive is nullptr.");
        return {};
    }

    Fill fill{};
    OHOS::MessageParcel data;
    (void)FillBlockMarshalling(data, fill);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertFullConnection(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertFullConnection v2_1 failed, primitive is nullptr.");
        return {};
    }

    FullConnection full_connection{};
    full_connection.hasBias = mindspore::lite::MindIR_FullConnection_GetHasBias(primitive);
    full_connection.useAxis = mindspore::lite::MindIR_FullConnection_GetUseAxis(primitive);
    full_connection.axis = mindspore::lite::MindIR_FullConnection_GetAxis(primitive);
    full_connection.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_FullConnection_GetActivationType(primitive));

    OHOS::MessageParcel data;
    (void)FullConnectionBlockMarshalling(data, full_connection);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertFusedBatchNorm(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertFusedBatchNorm v2_1 failed, primitive is nullptr.");
        return {};
    }

    FusedBatchNorm fused_batch_norm{};
    fused_batch_norm.epsilon = mindspore::lite::MindIR_FusedBatchNorm_GetEpsilon(primitive);
    OHOS::MessageParcel data;
    (void)FusedBatchNormBlockMarshalling(data, fused_batch_norm);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertGather(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertGather v2_1 failed, primitive is nullptr.");
        return {};
    }

    Gather gather{};
    OHOS::MessageParcel data;
    (void)GatherBlockMarshalling(data, gather);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertGreater(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertGreater v2_1 failed, primitive is nullptr.");
        return {};
    }

    Greater greater{};
    OHOS::MessageParcel data;
    (void)GreaterBlockMarshalling(data, greater);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertGreaterEqual(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertGreaterEqual v2_1 failed, primitive is nullptr.");
        return {};
    }

    GreaterEqual greaterEqual{};
    OHOS::MessageParcel data;
    (void)GreaterEqualBlockMarshalling(data, greaterEqual);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertInstanceNorm(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertInstanceNorm v2_1 failed, primitive is nullptr.");
        return {};
    }

    InstanceNorm instanceNorm{};
    instanceNorm.epsilon = mindspore::lite::MindIR_InstanceNorm_GetEpsilon(primitive);

    OHOS::MessageParcel data;
    (void)InstanceNormBlockMarshalling(data, instanceNorm);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertLayerNormFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertGather v2_1 failed, primitive is nullptr.");
        return {};
    }

    LayerNormFusion layer_norm_fusion{};
    layer_norm_fusion.beginNormAxis = mindspore::lite::MindIR_LayerNormFusion_GetBeginNormAxis(primitive);
    layer_norm_fusion.epsilon = mindspore::lite::MindIR_LayerNormFusion_GetEpsilon(primitive);
    layer_norm_fusion.elementwiseAffine = mindspore::lite::MindIR_LayerNormFusion_GetElementwiseAffine(primitive);
    layer_norm_fusion.beginParamsAxis = mindspore::lite::MindIR_LayerNormFusion_GetBeginParamsAxis(primitive);

    OHOS::MessageParcel data;
    (void)LayerNormFusionBlockMarshalling(data, layer_norm_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertLess(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertLess v2_1 failed, primitive is nullptr.");
        return {};
    }

    Less less{};
    OHOS::MessageParcel data;
    (void)LessBlockMarshalling(data, less);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertLessEqual(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertLessEqual v2_1 failed, primitive is nullptr.");
        return {};
    }

    LessEqual less_equal{};
    OHOS::MessageParcel data;
    (void)LessEqualBlockMarshalling(data, less_equal);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertLog(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertLog v2_1 failed, primitive is nullptr.");
        return {};
    }

    Log log{};

    OHOS::MessageParcel data;
    (void)LogBlockMarshalling(data, log);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertLogicalAnd(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertLogicalAnd v2_1 failed, primitive is nullptr.");
        return {};
    }

    LogicalAnd logicalAnd{};

    OHOS::MessageParcel data;
    (void)LogicalAndBlockMarshalling(data, logicalAnd);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertLogicalNot(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertLogicalNot v2_1 failed, primitive is nullptr.");
        return {};
    }

    LogicalNot logicalNot{};

    OHOS::MessageParcel data;
    (void)LogicalNotBlockMarshalling(data, logicalNot);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertLogicalOr(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertLogicalOr v2_1 failed, primitive is nullptr.");
        return {};
    }

    LogicalOr logicalOr{};

    OHOS::MessageParcel data;
    (void)LogicalOrBlockMarshalling(data, logicalOr);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertLstm(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertLstm v2_1 failed, primitive is nullptr.");
        return {};
    }

    LSTM lSTM{};
    lSTM.bidirectional = mindspore::lite::MindIR_LSTM_GetBidirectional(primitive);
    lSTM.has_bias = mindspore::lite::MindIR_LSTM_GetHasBias(primitive);
    lSTM.input_size = mindspore::lite::MindIR_LSTM_GetInputSize(primitive);
    lSTM.hidden_size = mindspore::lite::MindIR_LSTM_GetHiddenSize(primitive);
    lSTM.num_layers = mindspore::lite::MindIR_LSTM_GetNumLayers(primitive);
    lSTM.num_directions = mindspore::lite::MindIR_LSTM_GetNumDirections(primitive);
    lSTM.dropout = mindspore::lite::MindIR_LSTM_GetDropout(primitive);
    lSTM.zoneout_cell = mindspore::lite::MindIR_LSTM_GetZoneoutCell(primitive);
    lSTM.zoneout_hidden = mindspore::lite::MindIR_LSTM_GetZoneoutHidden(primitive);
    lSTM.proj_size = mindspore::lite::MindIR_LSTM_GetProjSize(primitive);

    OHOS::MessageParcel data;
    (void)LSTMBlockMarshalling(data, lSTM);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertMatMulFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertMatMulFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    MatMulFusion mat_mul_fusion{};
    mat_mul_fusion.transposeA = mindspore::lite::MindIR_MatMulFusion_GetTransposeA(primitive);
    mat_mul_fusion.transposeB = mindspore::lite::MindIR_MatMulFusion_GetTransposeB(primitive);
    mat_mul_fusion.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_MatMulFusion_GetActivationType(primitive));

    OHOS::MessageParcel data;
    (void)MatMulFusionBlockMarshalling(data, mat_mul_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertMaximum(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertMaximum v2_1 failed, primitive is nullptr.");
        return {};
    }

    Maximum maximum{};
    OHOS::MessageParcel data;
    (void)MaximumBlockMarshalling(data, maximum);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertMaxPoolFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertMaxPoolFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    MaxPoolFusion max_pool_fusion{};
    max_pool_fusion.kernelSize = mindspore::lite::MindIR_MaxPoolFusion_GetKernelSize(primitive);
    max_pool_fusion.strides = mindspore::lite::MindIR_MaxPoolFusion_GetStrides(primitive);
    max_pool_fusion.pad = mindspore::lite::MindIR_MaxPoolFusion_GetPad(primitive);
    max_pool_fusion.padMode = static_cast<PadMode>(mindspore::lite::MindIR_MaxPoolFusion_GetPadMode(primitive));
    max_pool_fusion.format = static_cast<Format>(mindspore::lite::MindIR_MaxPoolFusion_GetFormat(primitive));
    max_pool_fusion.roundMode = static_cast<RoundMode>(mindspore::lite::MindIR_MaxPoolFusion_GetRoundMode(primitive));
    max_pool_fusion.global = mindspore::lite::MindIR_MaxPoolFusion_GetGlobal(primitive);
    max_pool_fusion.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_MaxPoolFusion_GetActivationType(primitive));

    OHOS::MessageParcel data;
    (void)MaxPoolFusionBlockMarshalling(data, max_pool_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertMod(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertMod v2_1 failed, primitive is nullptr.");
        return {};
    }

    Mod mod{};

    OHOS::MessageParcel data;
    (void)ModBlockMarshalling(data, mod);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertMulFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertMulFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    MulFusion mul_fusion{};
    mul_fusion.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_MulFusion_GetActivationType(primitive));
    OHOS::MessageParcel data;
    (void)MulFusionBlockMarshalling(data, mul_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertNeg(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertNeg v2_1 failed, primitive is nullptr.");
        return {};
    }

    Neg neg{};

    OHOS::MessageParcel data;
    (void)NegBlockMarshalling(data, neg);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertNotEqual(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertNotEqual v2_1 failed, primitive is nullptr.");
        return {};
    }

    NotEqual notEqual{};

    OHOS::MessageParcel data;
    (void)NotEqualBlockMarshalling(data, notEqual);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertOneHot(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertOneHot v2_1 failed, primitive is nullptr.");
        return {};
    }

    OneHot one_hot{};
    one_hot.axis = mindspore::lite::MindIR_OneHot_GetAxis(primitive);
    OHOS::MessageParcel data;
    (void)OneHotBlockMarshalling(data, one_hot);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertPadFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertPadFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    PadFusion pad_fusion{};
    pad_fusion.paddings = mindspore::lite::MindIR_PadFusion_GetPaddings(primitive);
    pad_fusion.paddingMode = static_cast<PaddingMode>(mindspore::lite::MindIR_PadFusion_GetPaddingMode(primitive));
    pad_fusion.constantValue = mindspore::lite::MindIR_PadFusion_GetConstantValue(primitive);
    OHOS::MessageParcel data;
    (void)PadFusionBlockMarshalling(data, pad_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertPowFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertPowFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    PowFusion pow_fusion{};
    pow_fusion.scale = mindspore::lite::MindIR_PowFusion_GetScale(primitive);
    pow_fusion.shift = mindspore::lite::MindIR_PowFusion_GetShift(primitive);
    OHOS::MessageParcel data;
    (void)PowFusionBlockMarshalling(data, pow_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertPReLUFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertPReLUFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    PReLUFusion p_re_l_u_fusion{};
    p_re_l_u_fusion.channelShared = mindspore::lite::MindIR_PReLUFusion_GetChannelShared(primitive);
    OHOS::MessageParcel data;
    (void)PReLUFusionBlockMarshalling(data, p_re_l_u_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertQuantDTypeCast(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertPReLUFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    QuantDTypeCast quant_d_type_cast{};
    quant_d_type_cast.srcT = mindspore::lite::MindIR_QuantDTypeCast_GetSrcT(primitive);
    quant_d_type_cast.dstT = mindspore::lite::MindIR_QuantDTypeCast_GetDstT(primitive);
    OHOS::MessageParcel data;
    (void)QuantDTypeCastBlockMarshalling(data, quant_d_type_cast);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertRange(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertRange v2_1 failed, primitive is nullptr.");
        return {};
    }

    Range range{};
    range.d_type = mindspore::lite::MindIR_Range_GetDType(primitive);
    range.start = mindspore::lite::MindIR_Range_GetStart(primitive);
    range.limit = mindspore::lite::MindIR_Range_GetLimit(primitive);
    range.delta = mindspore::lite::MindIR_Range_GetDelta(primitive);

    OHOS::MessageParcel data;
    (void)RangeBlockMarshalling(data, range);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertReciprocal(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertReciprocal v2_1 failed, primitive is nullptr.");
        return {};
    }

    Reciprocal reciprocal{};

    OHOS::MessageParcel data;
    (void)ReciprocalBlockMarshalling(data, reciprocal);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertReduceFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertReduceFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    ReduceFusion reduce_fusion{};
    reduce_fusion.keepDims = mindspore::lite::MindIR_ReduceFusion_GetKeepDims(primitive);
    reduce_fusion.mode = static_cast<ReduceMode>(mindspore::lite::MindIR_ReduceFusion_GetMode(primitive));
    reduce_fusion.reduceToEnd = mindspore::lite::MindIR_ReduceFusion_GetReduceToEnd(primitive);
    reduce_fusion.coeff = mindspore::lite::MindIR_ReduceFusion_GetCoeff(primitive);
    OHOS::MessageParcel data;
    (void)ReduceFusionBlockMarshalling(data, reduce_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertReshape(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertReshape v2_1 failed, primitive is nullptr.");
        return {};
    }

    Reshape reshape{};
    OHOS::MessageParcel data;
    (void)ReshapeBlockMarshalling(data, reshape);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertResize(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertResize v2_1 failed, primitive is nullptr.");
        return {};
    }
 
    Resize resize{};
    resize.method = static_cast<ResizeMethod>(mindspore::lite::MindIR_Resize_GetMethod(primitive));
    resize.newHeight = mindspore::lite::MindIR_Resize_GetNewHeight(primitive);
    resize.newWidth = mindspore::lite::MindIR_Resize_GetNewWidth(primitive);
    resize.preserveAspectRatio = mindspore::lite::MindIR_Resize_GetPreserveAspectRatio(primitive);
    resize.coordinateTransformMode =
      static_cast<CoordinateTransformMode>(mindspore::lite::MindIR_Resize_GetCoordinateTransformMode(primitive));
    resize.cubicCoeff = mindspore::lite::MindIR_Resize_GetCubicCoeff(primitive);
    resize.excludeOutside = mindspore::lite::MindIR_Resize_GetExcludeOutside(primitive);
    resize.extrapolationValue = mindspore::lite::MindIR_Resize_GetExtrapolationValue(primitive);
    resize.nearestMode = static_cast<NearestMode>(mindspore::lite::MindIR_Resize_GetNearestMode(primitive));
    OHOS::MessageParcel data;
    (void)ResizeBlockMarshalling(data, resize);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertRsqrt(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertRsqrt v2_1 failed, primitive is nullptr.");
        return {};
    }

    Rsqrt rsqrt{};
    OHOS::MessageParcel data;
    (void)RsqrtBlockMarshalling(data, rsqrt);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertScaleFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertScaleFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    ScaleFusion scale_fusion{};
    scale_fusion.axis = mindspore::lite::MindIR_ScaleFusion_GetAxis(primitive);
    scale_fusion.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_ScaleFusion_GetActivationType(primitive));
    OHOS::MessageParcel data;
    (void)ScaleFusionBlockMarshalling(data, scale_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertShape(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertShape v2_1 failed, primitive is nullptr.");
        return {};
    }

    Shape shape{};
    OHOS::MessageParcel data;
    (void)ShapeBlockMarshalling(data, shape);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSin(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSin v2_1 failed, primitive is nullptr.");
        return {};
    }

    Sin sin{};

    OHOS::MessageParcel data;
    (void)SinBlockMarshalling(data, sin);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSliceFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSliceFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    SliceFusion slice_fusion{};
    slice_fusion.axes = mindspore::lite::MindIR_SliceFusion_GetAxes(primitive);
    OHOS::MessageParcel data;
    (void)SliceFusionBlockMarshalling(data, slice_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSoftmax(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSoftmax v2_1 failed, primitive is nullptr.");
        return {};
    }

    Softmax softmax{};
    softmax.axis = mindspore::lite::MindIR_Softmax_GetAxis(primitive);
    OHOS::MessageParcel data;
    (void)SoftmaxBlockMarshalling(data, softmax);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSpaceToBatchND(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSpaceToBatchND v2_1 failed, primitive is nullptr.");
        return {};
    }

    SpaceToBatchND space_to_batch_n_d{};
    space_to_batch_n_d.blockShape = mindspore::lite::MindIR_SpaceToBatchND_GetBlockShape(primitive);
    space_to_batch_n_d.paddings = mindspore::lite::MindIR_SpaceToBatchND_GetPaddings(primitive);
    OHOS::MessageParcel data;
    (void)SpaceToBatchNDBlockMarshalling(data, space_to_batch_n_d);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSparseToDense(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSparseToDense v2_1 failed, primitive is nullptr.");
        return {};
    }

    SparseToDense sparseToDense{};
    OHOS::MessageParcel data;
    (void)SparseToDenseBlockMarshalling(data, sparseToDense);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSplit(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSplit v2_1 failed, primitive is nullptr.");
        return {};
    }

    Split split{};
    split.outputNum = mindspore::lite::MindIR_Split_GetOutputNum(primitive);
    split.sizeSplits = mindspore::lite::MindIR_Split_GetSizeSplits(primitive);
    split.axis = mindspore::lite::MindIR_Split_GetAxis(primitive);
    OHOS::MessageParcel data;
    (void)SplitBlockMarshalling(data, split);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSqrt(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSqrt v2_1 failed, primitive is nullptr.");
        return {};
    }

    Sqrt sqrt{};
    OHOS::MessageParcel data;
    (void)SqrtBlockMarshalling(data, sqrt);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSquare(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSquare v2_1 failed, primitive is nullptr.");
        return {};
    }

    Square square{};
    OHOS::MessageParcel data;
    (void)SquareBlockMarshalling(data, square);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSquaredDifference(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSquaredDifference v2_1 failed, primitive is nullptr.");
        return {};
    }

    SquaredDifference squared_difference{};
    OHOS::MessageParcel data;
    (void)SquaredDifferenceBlockMarshalling(data, squared_difference);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSqueeze(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSqueeze v2_1 failed, primitive is nullptr.");
        return {};
    }

    Squeeze squeeze{};
    squeeze.axis = mindspore::lite::MindIR_Squeeze_GetAxis(primitive);
    OHOS::MessageParcel data;
    (void)SqueezeBlockMarshalling(data, squeeze);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertStack(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertStack v2_1 failed, primitive is nullptr.");
        return {};
    }

    Stack stack{};
    stack.axis = mindspore::lite::MindIR_Stack_GetAxis(primitive);
    OHOS::MessageParcel data;
    (void)StackBlockMarshalling(data, stack);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertStridedSlice(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertStridedSlice v2_1 failed, primitive is nullptr.");
        return {};
    }

    StridedSlice strided_slice{};
    strided_slice.beginMask = mindspore::lite::MindIR_StridedSlice_GetBeginMask(primitive);
    strided_slice.endMask = mindspore::lite::MindIR_StridedSlice_GetEndMask(primitive);
    strided_slice.ellipsisMask = mindspore::lite::MindIR_StridedSlice_GetEllipsisMask(primitive);
    strided_slice.newAxisMask = mindspore::lite::MindIR_StridedSlice_GetNewAxisMask(primitive);
    strided_slice.shrinkAxisMask = mindspore::lite::MindIR_StridedSlice_GetShrinkAxisMask(primitive);
    OHOS::MessageParcel data;
    (void)StridedSliceBlockMarshalling(data, strided_slice);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSubFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSubFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    SubFusion sub_fusion{};
    sub_fusion.activationType = static_cast<ActivationType>(
        mindspore::lite::MindIR_SubFusion_GetActivationType(primitive));
    OHOS::MessageParcel data;
    (void)SubFusionBlockMarshalling(data, sub_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertTileFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertTileFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    TileFusion tile_fusion{};
    tile_fusion.dims = mindspore::lite::MindIR_TileFusion_GetDims(primitive);
    OHOS::MessageParcel data;
    (void)TileFusionBlockMarshalling(data, tile_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertTopKFusion(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertTopKFusion v2_1 failed, primitive is nullptr.");
        return {};
    }

    TopKFusion top_k_fusion{};
    top_k_fusion.sorted = mindspore::lite::MindIR_TopKFusion_GetSorted(primitive);
    top_k_fusion.axis = mindspore::lite::MindIR_TopKFusion_GetAxis(primitive);
    OHOS::MessageParcel data;
    (void)TopKFusionBlockMarshalling(data, top_k_fusion);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertTranspose(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertTranspose v2_1 failed, primitive is nullptr.");
        return {};
    }

    Transpose transpose{};
    OHOS::MessageParcel data;
    (void)TransposeBlockMarshalling(data, transpose);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertUnsqueeze(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertUnsqueeze v2_1 failed, primitive is nullptr.");
        return {};
    }

    Unsqueeze unsqueeze{};
    unsqueeze.axis = mindspore::lite::MindIR_Unsqueeze_GetAxis(primitive);
    OHOS::MessageParcel data;
    (void)UnsqueezeBlockMarshalling(data, unsqueeze);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertUnstack(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertUnstack v2_1 failed, primitive is nullptr.");
        return {};
    }

    Unstack unstack{};
    unstack.axis = mindspore::lite::MindIR_Unstack_GetAxis(primitive);

    OHOS::MessageParcel data;
    (void)UnstackBlockMarshalling(data, unstack);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertWhere(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertWhere v2_1 failed, primitive is nullptr.");
        return {};
    }

    Where where{};

    OHOS::MessageParcel data;
    (void)WhereBlockMarshalling(data, where);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertSelect(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertSelect v2_1 failed, primitive is nullptr.");
        return {};
    }

    Select select{};

    OHOS::MessageParcel data;
    (void)SelectBlockMarshalling(data, select);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> ConvertErf(PrimitivePtr primitive)
{
    if (primitive == nullptr) {
        LOGE("ConvertErf v2_1 failed, primitive is nullptr.");
        return {};
    }

    Erf erf{};

    OHOS::MessageParcel data;
    (void)ErfBlockMarshalling(data, erf);
    std::vector<int8_t> ret(reinterpret_cast<const int8_t *>(data.GetData()),
                            reinterpret_cast<const int8_t *>(data.GetData()) + data.GetDataSize());
    return ret;
}

std::vector<int8_t> Convert(OHOS::HDI::Nnrt::V2_1::NodeType type, PrimitivePtr primitive)
{
    switch (type) {
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_ACTIVATION:
            return ConvertActivation(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_ADD_FUSION:
            return ConvertAddFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_ALL:
            return ConvertAll(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_ARGMAX_FUSION:
            return ConvertArgMaxFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_ASSERT:
            return ConvertAssert(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_AVGPOOL_FUSION:
            return ConvertAvgPoolFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_BATCH_TO_SPACE_ND:
            return ConvertBatchToSpaceND(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_BIAS_ADD:
            return ConvertBiasAdd(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_BROADCAST_TO:
            return ConvertBroadcastTo(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_CAST:
            return ConvertCast(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_CLIP:
            return ConvertClip(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_CONCAT:
            return ConvertConcat(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_CONV2D_FUSION:
            return ConvertConv2DFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_CONV2D_TRANSPOSE_FUSION:
            return ConvertConv2dTransposeFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_COS:
            return ConvertCos(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_CONSTANT_OF_SHAPE:
            return ConvertConstantOfShape(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_DEPTH_TO_SPACE:
            return ConvertDepthToSpace(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_DIV_FUSION:
            return ConvertDivFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_ELTWISE:
            return ConvertEltwise(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_EQUAL:
            return ConvertEqual(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_EXPFUSION:
            return ConvertExpFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_EXPAND_DIMS:
            return ConvertExpandDims(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_FLATTEN:
            return ConvertFlatten(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_FILL:
            return ConvertFill(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_FULL_CONNECTION:
            return ConvertFullConnection(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_FUSED_BATCH_NORM:
            return ConvertFusedBatchNorm(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_GATHER:
            return ConvertGather(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_GREATER:
            return ConvertGreater(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_GREATER_EQUAL:
            return ConvertGreaterEqual(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_INSTANCE_NORM:
            return ConvertInstanceNorm(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_LAYER_NORM_FUSION:
            return ConvertLayerNormFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_LESS:
            return ConvertLess(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_LESS_EQUAL:
            return ConvertLessEqual(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_LOG:
            return ConvertLog(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_LOGICAL_AND:
            return ConvertLogicalAnd(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_LOGICAL_NOT:
            return ConvertLogicalNot(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_LOGICAL_OR:
            return ConvertLogicalOr(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_LSTM:
            return ConvertLstm(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_MATMUL_FUSION:
            return ConvertMatMulFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_MAXIMUM:
            return ConvertMaximum(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_MAX_POOL_FUSION:
            return ConvertMaxPoolFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_MOD:
            return ConvertMod(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_MUL_FUSION:
            return ConvertMulFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_NEG:
            return ConvertNeg(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_NOT_EQUAL:
            return ConvertNotEqual(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_ONE_HOT:
            return ConvertOneHot(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_PAD_FUSION:
            return ConvertPadFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_POW_FUSION:
            return ConvertPowFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_PRELU_FUSION:
            return ConvertPReLUFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_QUANT_DTYPE_CAST:
            return ConvertQuantDTypeCast(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_RANGE:
            return ConvertRange(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_RECIPROCAL:
            return ConvertReciprocal(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_REDUCE_FUSION:
            return ConvertReduceFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_RESHAPE:
            return ConvertReshape(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_RESIZE:
            return ConvertResize(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_RSQRT:
            return ConvertRsqrt(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SCALE_FUSION:
            return ConvertScaleFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SHAPE:
            return ConvertShape(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SIN:
            return ConvertSin(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SLICE_FUSION:
            return ConvertSliceFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SOFTMAX:
            return ConvertSoftmax(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SPACE_TO_BATCH_ND:
            return ConvertSpaceToBatchND(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SPARSE_TO_DENSE:
            return ConvertSparseToDense(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SPLIT:
            return ConvertSplit(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SQRT:
            return ConvertSqrt(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SQUARED_DIFFERENCE:
            return ConvertSquaredDifference(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SQUEEZE:
            return ConvertSqueeze(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SQUARE:
            return ConvertSquare(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_STACK:
            return ConvertStack(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_STRIDED_SLICE:
            return ConvertStridedSlice(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SUB_FUSION:
            return ConvertSubFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_TILE_FUSION:
            return ConvertTileFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_TOPK_FUSION:
            return ConvertTopKFusion(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_TRANSPOSE:
            return ConvertTranspose(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_UNSQUEEZE:
            return ConvertUnsqueeze(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_UNSTACK:
            return ConvertUnstack(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_WHERE:
            return ConvertWhere(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_SELECT:
            return ConvertSelect(primitive);
            break;
        case OHOS::HDI::Nnrt::V2_1::NODE_TYPE_ERF:
            return ConvertErf(primitive);
            break;
        default:
            return {};
    }
}

inline std::vector<OHOS::HDI::Nnrt::V2_1::QuantParam> MindIR_Tensor_GetQuantParams_OHOS(TensorPtr tensor)
{
    if (tensor != nullptr) {
        std::vector<OHOS::HDI::Nnrt::V2_1::QuantParam> result;
        auto src = mindspore::lite::MindIR_Tensor_GetQuantParams(tensor);
        if (src.empty()) {
            return {};
        }
        size_t size = src.size();
        for (size_t i = 0; i < size; i++) {
            OHOS::HDI::Nnrt::V2_1::QuantParam quantParam{src[i].numBits, src[i].zeroPoint, src[i].scale};
            result.emplace_back(quantParam);
        }
        return result;
    } else {
        return {};
    }
}

void HDIModel_Destroy(OHOS::HDI::Nnrt::V2_1::Model **model)
{
    if (model != nullptr && *model != nullptr) {
        auto model_data = *model;
        delete (model_data);
        *model = nullptr;
    }
}

OHOS::HDI::Nnrt::V2_1::SharedBuffer Copy_MindIR_Tensor_Data_To_HDIBuffer(const TensorPtr tensor,
    const OHOS::HDI::Nnrt::V2_1::SharedBuffer &buffer_templete, uint8_t *mmap_ptr, unsigned int offset)
{
    if (tensor == nullptr) {
        LOGE("");
        return {-1, 0, offset, 0};
    }
    if (mmap_ptr == nullptr) {
        LOGE("Tensor GetData failed, mmap pointer should not be nullptr");
        return {-1, 0, offset, 0};
    }

    OHOS::HDI::Nnrt::V2_1::SharedBuffer result{};
    std::vector<uint8_t> data = mindspore::lite::MindIR_Tensor_GetData(tensor);
    if (data.empty()) {
        result.fd = -1;
        result.bufferSize = buffer_templete.bufferSize;
        result.offset = offset;
        result.dataSize = 0;
        return result;
    }
    result.fd = buffer_templete.fd;
    result.bufferSize = buffer_templete.bufferSize;
    auto ret = memcpy_s(mmap_ptr + offset, data.size(), data.data(), data.size());
    if (ret != EOK) {
        LOGE("Tensor memcpy failed.");
        return {-1, 0, offset, 0};
    }
    result.offset = offset;
    result.dataSize = data.size();
    return result;
}

OHOS::HDI::Nnrt::V2_1::Model *LiteGraph_To_HDIModel(const mindspore::lite::LiteGraph *lite_graph,
    const OHOS::HDI::Nnrt::V2_1::SharedBuffer &buffer)
{
    if (lite_graph == nullptr) {
        LOGE("MindIR_LiteGraph_To_Model v2_1 failed, lite graph is nullptr.");
        return nullptr;
    }

    LOGI("MindIR_LiteGraph_To_Model begin"); // todo 改称hitrace

    std::vector<uint32_t> inputIndex;
    std::vector<uint32_t> outputIndex;
    std::vector<OHOS::HDI::Nnrt::V2_1::Node> nodes;
    std::vector<OHOS::HDI::Nnrt::V2_1::Tensor> allTensors;
    std::vector<OHOS::HDI::Nnrt::V2_1::SubGraph> subGraph;

    // nodes
    for (auto node : lite_graph->all_nodes_) {
        if (node == nullptr) {
            LOGE("MindIR_LiteGraph_To_Model v2_1 failed, node is nullptr.");
            return nullptr;
        }
        OHOS::HDI::Nnrt::V2_1::Node tmp;
        tmp.name = node->name_;
        if (node->primitive_ == nullptr) {
            LOGE("MindIR_LiteGraph_To_Model v2_1 failed, node primitive is nullptr.");
            return nullptr;
        }
        tmp.nodeType = static_cast<OHOS::HDI::Nnrt::V2_1::NodeType>(
            mindspore::lite::MindIR_Primitive_GetType(node->primitive_));
        tmp.nodeAttr = Convert(tmp.nodeType, node->primitive_);
        tmp.inputIndex = node->input_indices_;
        tmp.outputIndex = node->output_indices_;
        tmp.quantType = static_cast<QuantType>(node->quant_type_);
        nodes.emplace_back(tmp);
    }

    // Tensor
    unsigned int tensor_buffer_offset = 0;
    uint8_t *mmap_ptr = nullptr;
    if (buffer.fd != -1) {
        mmap_ptr =
          static_cast<uint8_t *>(mmap(nullptr, buffer.bufferSize, PROT_READ | PROT_WRITE, MAP_SHARED, buffer.fd, 0));
        if (mmap_ptr == MAP_FAILED) {
            LOGE("MindIR_LiteGraph_To_Model v2_1 failed, mmap failed.");
            return nullptr;
        }
    }
    for (auto tensor : lite_graph->all_tensors_) {
        OHOS::HDI::Nnrt::V2_1::Tensor tmp;
        tmp.name = mindspore::lite::MindIR_Tensor_GetName(tensor);
        tmp.dataType = static_cast<DataType>(mindspore::lite::MindIR_Tensor_GetDataType(tensor));
        tmp.dims = mindspore::lite::MindIR_Tensor_GetDims(tensor);
        tmp.format = static_cast<Format>(mindspore::lite::MindIR_Tensor_GetFormat(tensor));
        tmp.data = Copy_MindIR_Tensor_Data_To_HDIBuffer(tensor, buffer, mmap_ptr, tensor_buffer_offset); // todo 实现
        tmp.quantParams = MindIR_Tensor_GetQuantParams_OHOS(tensor);
        allTensors.emplace_back(tmp);
        tensor_buffer_offset = tmp.data.offset + tmp.data.dataSize;
    }
    if (buffer.fd != -1) {
        auto munmap_res = munmap(mmap_ptr, buffer.bufferSize);
        if (munmap_res != 0) {
            LOGE("MindIR_LiteGraph_To_Model v2_1 failed, unmap failed.");
            return nullptr;
        }
    }

    // SubGraph
    for (auto graph : lite_graph->sub_graphs_) {
        OHOS::HDI::Nnrt::V2_1::SubGraph tmp;
        tmp.name = graph->name_;
        tmp.inputIndices = std::vector<uint32_t>(graph->input_indices_);
        tmp.outputIndices = std::vector<uint32_t>(graph->output_indices_);
        tmp.nodeIndices = std::vector<uint32_t>(graph->node_indices_);
        subGraph.emplace_back(tmp);
    }

    auto *ret_model = new (std::nothrow) OHOS::HDI::Nnrt::V2_1::Model();
    if (ret_model == nullptr) {
        LOGE("MindIR_LiteGraph_To_Model v2_1 failed, new Model failed.");
        return nullptr;
    }
    ret_model->name = lite_graph->name_;
    ret_model->inputIndex = lite_graph->input_indices_;
    ret_model->outputIndex = lite_graph->output_indices_;
    ret_model->nodes = nodes;
    ret_model->allTensors = allTensors;
    ret_model->subGraph = subGraph;
    return ret_model;
}
} // NNRt_V2_1
} // NeuralNetworkRuntime
} // OHOS