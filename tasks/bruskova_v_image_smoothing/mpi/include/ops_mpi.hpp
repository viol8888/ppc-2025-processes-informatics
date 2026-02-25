#pragma once

#include <vector>
#include <tuple>
#include <mpi.h>
#include "task/include/task.hpp"

namespace bruskova_v_image_smoothing {

using InType = std::tuple<std::vector<int>, int, int>;
using OutType = std::vector<int>;
using BaseTask = ppc::task::Task<InType, OutType>;

class BruskovaVImageSmoothingMPI : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kMPI;
  }
  explicit BruskovaVImageSmoothingMPI(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  std::vector<int> input_img_;
  int width_, height_;
  std::vector<int> result_img_;
};

}  // namespace bruskova_v_image_smoothing