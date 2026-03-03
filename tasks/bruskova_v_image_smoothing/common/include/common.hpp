#pragma once
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

#ifndef PPC_SETTINGS_bruskova_v_image_smoothing
#  define PPC_SETTINGS_bruskova_v_image_smoothing "bruskova_v_image_smoothing"
#endif

namespace bruskova_v_image_smoothing {
using InType = std::tuple<std::vector<int>, int, int>;
using OutType = std::vector<int>;
using TestType = std::tuple<InType, OutType>;
using BaseTask = ppc::task::Task<InType, OutType>;
}  // namespace bruskova_v_image_smoothing
