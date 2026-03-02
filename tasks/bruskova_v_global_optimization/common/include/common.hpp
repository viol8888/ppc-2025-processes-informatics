#pragma once
#include <string>
#include <tuple>
#include <vector>

#include "task/include/task.hpp"
namespace bruskova_v_global_optimization {
using InType = std::vector<double>;
using OutType = double;
using TestType = std::tuple<int>;
using BaseTask = ppc::task::Task<InType, OutType>;
}  // namespace bruskova_v_global_optimization
