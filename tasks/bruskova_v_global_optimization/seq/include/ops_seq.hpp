#pragma once
#include <vector>

#include "bruskova_v_global_optimization/common/include/common.hpp"
#include "task/include/task.hpp"

namespace bruskova_v_global_optimization {

class BruskovaVGlobalOptimizationSEQ : public ppc::task::Task<InType, OutType> {
 public:
  explicit BruskovaVGlobalOptimizationSEQ(const InType& in) : ppc::task::Task<InType, OutType>(in) {}

  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }

 private:
  double x_min_ = 0.0, x_max_ = 0.0, y_min_ = 0.0, y_max_ = 0.0, step_ = 0.0;
  std::vector<double> result_;
};

}  // namespace bruskova_v_global_optimization
