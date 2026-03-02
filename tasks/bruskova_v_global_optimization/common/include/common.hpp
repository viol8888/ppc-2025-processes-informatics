#pragma once
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

#ifndef PPC_SETTINGS_bruskova_v_global_optimization
#  define PPC_SETTINGS_bruskova_v_global_optimization "bruskova_v_global_optimization"
#endif

namespace bruskova_v_global_optimization {
using InType = std::vector<double>;
using OutType = std::vector<double>;
using TestType = std::tuple<InType, OutType>;
using BaseTask = ppc::task::Task<InType, OutType>;
}  // namespace bruskova_v_global_optimization
