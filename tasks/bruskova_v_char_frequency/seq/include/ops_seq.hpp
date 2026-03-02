#pragma once

#include <string>
#include <vector>

#include "bruskova_v_char_frequency/common/include/common.hpp"
#include "task/include/task.hpp"

namespace bruskova_v_char_frequency {
using InType = uint8_t;
using OutType = uint8_t;

class BruskovaVCharFrequencySEQ : public BaseTask {
  using BaseTask = ppc::task::Task<InType, OutType>;

 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }
  explicit BruskovaVCharFrequencySEQ(const InType &in);

  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

 private:
  std::string input_str_;
  char target_char_;
  int result_count_ = 0;
};

}  // namespace bruskova_v_char_frequency
