#include "../include/ops_seq.hpp"
#include <limits>

namespace bruskova_v_global_optimization {

BruskovaVGlobalOptimizationSEQ::BruskovaVGlobalOptimizationSEQ(const InType &in) : BaseTask(in) {}

bool BruskovaVGlobalOptimizationSEQ::ValidationImpl() {

  return this->in_.size() == 5 && this->in_[4] > 0;
}

bool BruskovaVGlobalOptimizationSEQ::PreProcessingImpl() {
  x_min_ = this->in_[0];
  x_max_ = this->in_[1];
  y_min_ = this->in_[2];
  y_max_ = this->in_[3];
  step_  = this->in_[4];
  

  result_ = {std::numeric_limits<double>::max(), 0.0, 0.0};
  return true;
}

bool BruskovaVGlobalOptimizationSEQ::RunImpl() {

  for (double x = x_min_; x <= x_max_; x += step_) {
    for (double y = y_min_; y <= y_max_; y += step_) {
      double val = x * x + y * y;
      if (val < result_[0]) {
        result_[0] = val; 
        result_[1] = x;   
        result_[2] = y;   
      }
    }
  }
  return true;
}

bool BruskovaVGlobalOptimizationSEQ::PostProcessingImpl() {
  this->out_ = result_;
  return true;
}

}  // namespace bruskova_v_global_optimization