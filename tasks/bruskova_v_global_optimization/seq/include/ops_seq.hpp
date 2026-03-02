#pragma once
#include <vector>

#include "bruskova_v_global_optimization/common/include/common.hpp"

namespace bruskova_v_global_optimization {

class BruskovaVGlobalOptimizationSEQ : public BaseTask {
 public:
  explicit BruskovaVGlobalOptimizationSEQ(const InType &in);
  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }

 private:
  double x_min_, x_max_, y_min_, y_max_, step_;
  std::vector<double> result_;
};

}  // namespace bruskova_v_global_optimization

