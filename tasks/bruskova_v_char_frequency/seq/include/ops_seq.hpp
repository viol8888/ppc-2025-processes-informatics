#pragma once

#include <string>
#include <vector>

#include "bruskova_v_char_frequency/common/include/common.hpp"
#include "task/include/task.hpp"

namespace bruskova_v_char_frequency {

class BruskovaVCharFrequencySEQ : public ppc::task::Task<InType, OutType> {
  using BaseTask = ppc::task::Task<InType, OutType>;
 public:
  explicit BruskovaVCharFrequencySEQ(const InType &in) : ppc::task::Task<InType, OutType>() {}
  

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
