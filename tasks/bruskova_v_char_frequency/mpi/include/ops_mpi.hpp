#pragma once

#include <string>
#include <vector>

#include "bruskova_v_char_frequency/common/include/common.hpp"
// #include "task/include/task.hpp"

namespace bruskova_v_char_frequency {

class BruskovaVCharFrequencyMPI : public ppc::Task<InType, OutType> {
 public:
  explicit BruskovaVCharFrequencyMPI(const InType &in) : ppc::Task<InType, OutType>(in) {}
  explicit BruskovaVCharFrequencyMPI(const ppc::TaskData &data) : ppc::Task<InType, OutType>(data) {}

  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  ppc::TaskType GetTaskType() const override {
    return ppc::TaskType::TASK;
  }

 private:
  std::string input_str_;
  char target_char_;
  int result_count_ = 0;
};

}  // namespace bruskova_v_char_frequency
