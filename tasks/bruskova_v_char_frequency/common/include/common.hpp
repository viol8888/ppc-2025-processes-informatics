#pragma once
#include <string>
#include <tuple>
#include <vector>

#include "task/include/task.hpp"

namespace bruskova_v_char_frequency {
using InType = std::string;
using OutType = int;
using TestType = std::tuple<int>;
using BaseTask = ppc::task::Task<InType, OutType>;
}  // namespace bruskova_v_char_frequency
