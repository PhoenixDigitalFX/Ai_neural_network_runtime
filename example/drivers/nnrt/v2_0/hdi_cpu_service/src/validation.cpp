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

#include "validation.h"

namespace OHOS {
namespace HDI {
namespace Nnrt {
namespace V2_0 {
int32_t ValidatePerformanceMode(PerformanceMode mode)
{
    if (mode < PerformanceMode::PERFORMANCE_NONE || mode > PerformanceMode::PERFORMANCE_EXTREME) {
        return false;
    }

    return true;
}

int32_t ValidatePriority(Priority priority)
{
    if (priority < Priority::PRIORITY_NONE || priority > Priority::PRIORITY_HIGH) {
        return false;
    }

    return true;
}

int32_t ValidateDataType(DataType dataType)
{
    if (dataType < DataType::DATA_TYPE_UNKNOWN || dataType > DataType::DATA_TYPE_FLOAT64) {
        return false;
    }

    if (dataType > DataType::DATA_TYPE_UNKNOWN && dataType < DataType::DATA_TYPE_BOOL) {
        return false;
    }

    if (dataType > DataType::DATA_TYPE_BOOL && dataType < DataType::DATA_TYPE_INT8) {
        return false;
    }

    if (dataType > DataType::DATA_TYPE_UINT64 && dataType < DataType::DATA_TYPE_FLOAT16) {
        return false;
    }

    return true;
}

int32_t ValidateFormat(Format format)
{
    if (format < Format::FORMAT_NONE || format > Format::FORMAT_NHWC) {
        return false;
    }

    return true;
}
} // namespace V2_0
} // namespace Nnrt
} // namespace HDI
} // namespace OHOS