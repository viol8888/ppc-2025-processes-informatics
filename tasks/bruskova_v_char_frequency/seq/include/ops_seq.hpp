#pragma once

#include <string>
#include <utility>
#include "task/include/task.hpp"

namespace bruskova_v_char_frequency {

using InType = std::pair<std::string, char>; 

using OutType = int;                         
using BaseTask = ppc::task::Task<InType, OutType>;

class BruskovaVCharFrequencySEQ : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }
  
  
  explicit BruskovaVCharFrequencySEQ(const InType &in);

 private:
  
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  
  std::string input_str_;
  char target_char_;
  int result_count_;
};

}  // namespace bruskova_v_char_frequency