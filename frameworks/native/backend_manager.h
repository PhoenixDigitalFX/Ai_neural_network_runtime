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

#ifndef NEURAL_NETWORK_CORE_BACKEND_MANAGER_H
#define NEURAL_NETWORK_CORE_BACKEND_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include <functional>

#include "backend.h"

namespace OHOS {
namespace NeuralNetworkRuntime {
class BackendManager {
public:
    const std::vector<size_t>& GetAllBackendsID();
    std::shared_ptr<Backend> GetBackend(size_t backendID) const;
    const std::string& GetBackendName(size_t backendID);

    // Register backend by C++ API
    OH_NN_ReturnCode RegisterBackend(std::function<std::shared_ptr<Backend>()> creator);

    static BackendManager& GetInstance()
    {
        static BackendManager instance;
        return instance;
    }

private:
    BackendManager() = default;
    BackendManager(const BackendManager&) = delete;
    BackendManager& operator=(const BackendManager&) = delete;
    virtual ~BackendManager();
    bool IsValidBackend(std::shared_ptr<Backend> backend) const;

private:
    std::unordered_set<size_t> m_backendIDs;
    // key is the name of backend.
    std::unordered_map<size_t, std::shared_ptr<Backend>> m_backends;
    std::mutex m_mtx;

    std::string m_tmpBackendName;
    std::vector<size_t> m_tmpBackendIds;
};
}  // namespace NeuralNetworkRuntime
}  // namespace OHOS
#endif  // NEURAL_NETWORK_CORE_BACKEND_MANAGER_H
