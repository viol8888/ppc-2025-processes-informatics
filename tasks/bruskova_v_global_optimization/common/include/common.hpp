#pragma once

#include <vector>
#include <tuple>
#include "task/include/task.hpp"

namespace bruskova_v_global_optimization {

using InType = std::vector<double>;
using OutType = std::vector<double>;
using TestType = std::tuple<InType, OutType>;
using BaseTask = ppc::task::Task<InType, OutType>;

}  // namespace bruskova_v_global_optimization