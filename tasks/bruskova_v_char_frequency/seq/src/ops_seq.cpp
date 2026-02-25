#include "../include/ops_seq.hpp"

namespace bruskova_v_char_frequency {

BruskovaVCharFrequencySEQ::BruskovaVCharFrequencySEQ(const InType &in) : BaseTask(in) {}


bool BruskovaVCharFrequencySEQ::ValidationImpl() {

  return !this->in_.first.empty(); 
}


bool BruskovaVCharFrequencySEQ::PreProcessingImpl() {
  input_str_ = this->in_.first;     
  target_char_ = this->in_.second;  
  result_count_ = 0;                
  return true;
}

bool BruskovaVCharFrequencySEQ::RunImpl() {
  for (char c : input_str_) {
    if (c == target_char_) {
      result_count_++;
    }
  }
  return true;
}

bool BruskovaVCharFrequencySEQ::PostProcessingImpl() {
  this->out_ = result_count_;
  return true;
}

}  // namespace bruskova_v_char_frequency