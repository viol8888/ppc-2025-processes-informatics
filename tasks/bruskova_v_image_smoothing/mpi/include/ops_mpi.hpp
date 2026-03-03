#pragma once

#include <vector>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
#include "task/include/task.hpp"

namespace bruskova_v_image_smoothing {

class BruskovaVImageSmoothingMPI : public ppc::task::Task<InType, OutType> {
 public:
  explicit BruskovaVImageSmoothingMPI(const InType &in) : ppc::task::Task<InType, OutType>(in) {}

  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kMPI;
  }

 private:
  std::vector<int> input_img_;
  std::vector<int> result_img_;
  int width_ = 0;
  int height_ = 0;
};

}  // namespace bruskova_v_image_smoothing
