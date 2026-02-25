#pragma once

#include <vector>
#include <tuple>
#include "task/include/task.hpp"

namespace bruskova_v_image_smoothing {

using InType = std::tuple<std::vector<int>, int, int>;
using OutType = std::vector<int>;
using TestType = std::tuple<InType, OutType>;
using BaseTask = ppc::task::Task<InType, OutType>;

}  // namespace bruskova_v_image_smoothing