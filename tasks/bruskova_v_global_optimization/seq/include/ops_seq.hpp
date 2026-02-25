#pragma once

#include <vector>
#include "bruskova_v_global_optimization/common/include/common.hpp"
#include "task/include/task.hpp"

namespace bruskova_v_global_optimization {

using InType = std::vector<double>; 
using OutType = std::vector<double>;
using BaseTask = ppc::task::Task<InType, OutType>;

class BruskovaVGlobalOptimizationSEQ : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }
  explicit BruskovaVGlobalOptimizationSEQ(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  double x_min_, x_max_, y_min_, y_max_, step_;
  std::vector<double> result_;
};

}  // namespace bruskova_v_global_optimization