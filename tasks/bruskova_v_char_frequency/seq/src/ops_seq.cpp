#include "../include/ops_seq.hpp"

namespace bruskova_v_char_frequency {

BruskovaVCharFrequencySEQ::BruskovaVCharFrequencySEQ(const InType &in) : BaseTask() {
  this->GetInput() = in;
}

bool BruskovaVCharFrequencySEQ::ValidationImpl() {
  return true;
}

bool BruskovaVCharFrequencySEQ::PreProcessingImpl() {
  const auto &in = this->GetInput();
  input_str_ = in.first;
  target_char_ = in.second;
  return true;
}

bool BruskovaVCharFrequencySEQ::RunImpl() {
  result_count_ = 0;
  for (char c : input_str_) {
    if (c == target_char_) {
      result_count_++;
    }
  }
  return true;
}

bool BruskovaVCharFrequencySEQ::PostProcessingImpl() {
  this->GetOutput() = result_count_;
  return true;
}

}  // namespace bruskova_v_char_frequency
