#include "../include/ops_seq.hpp"

#include <limits>
#include <vector>

namespace bruskova_v_global_optimization {

BruskovaVGlobalOptimizationSEQ::BruskovaVGlobalOptimizationSEQ(const InType &in) : BaseTask() {
  this->GetInput() = in;
}

bool BruskovaVGlobalOptimizationSEQ::ValidationImpl() {
  const auto &in = this->GetInput();
  return in.size() == 5 && in[4] > 0;
}
bool BruskovaVGlobalOptimizationSEQ::PreProcessingImpl() {
  const auto &in = this->GetInput();
  x_min_ = in[0];
  x_max_ = in[1];
  y_min_ = in[2];
  y_max_ = in[3];
  step_ = in[4];

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
  this->GetOutput() = result_;
  return true;
}

}  // namespace bruskova_v_global_optimization

