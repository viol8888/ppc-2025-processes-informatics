#pragma once

#include <vector>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
#include "core/include/task.hpp"

namespace bruskova_v_image_smoothing {

class BruskovaVImageSmoothingMPI : public ppc::core::Task<InType, OutType> {
 public:
  explicit BruskovaVImageSmoothingMPI(const InType &in) : ppc::core::Task<InType, OutType>(in) {}

  explicit BruskovaVImageSmoothingMPI(const ppc::core::TaskData &data) : ppc::core::Task<InType, OutType>(data) {}

  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  ppc::core::TaskType GetTaskType() const override {
    return ppc::core::TaskType::TASK;
  }

 private:
  std::vector<int> input_img_;
  std::vector<int> result_img_;
  int width_ = 0, height_ = 0;
};

}  // namespace bruskova_v_image_smoothing