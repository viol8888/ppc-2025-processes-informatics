#pragma once

#include <vector>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
// #include "task/include/task.hpp"

namespace bruskova_v_image_smoothing {
using InType = uint8_t;
using OutType = uint8_t;

class BruskovaVImageSmoothingMPI : public BaseTask {
  using BaseTask = ppc::task::Task<InType, OutType>;

 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kMPI;
  }
  explicit BruskovaVImageSmoothingMPI(const InType &in);

  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

 private:
  std::vector<int> input_img_;
  std::vector<int> result_img_;
  int width_ = 0;
  int height_ = 0;
};

}  // namespace bruskova_v_image_smoothing

