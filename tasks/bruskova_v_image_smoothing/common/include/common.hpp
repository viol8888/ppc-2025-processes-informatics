#pragma once
#include <string>
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

namespace bruskova_v_image_smoothing {
using InType = std::vector<int>;
using OutType = std::vector<int>;
using TestType = std::tuple<int>;
using BaseTask = ppc::task::Task<InType, OutType>;
}  // namespace bruskova_v_image_smoothing
