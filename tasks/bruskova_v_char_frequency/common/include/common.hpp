#pragma once

#include <string>
#include <utility>
#include <tuple>
#include "task/include/task.hpp"

namespace bruskova_v_char_frequency {

using InType = std::pair<std::string, char>;
using OutType = int;
using TestType = std::tuple<InType, OutType>;
using BaseTask = ppc::task::Task<InType, OutType>;

}  // namespace bruskova_v_char_frequency