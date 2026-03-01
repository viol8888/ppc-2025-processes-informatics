#include <vector>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
#include "task/include/task.hpp"

namespace bruskova_v_image_smoothing {

class BruskovaVImageSmoothingMPI : public ppc::Task<InType, OutType> {
 public:
  explicit BruskovaVImageSmoothingMPI(const InType &in) : ppc::Task<InType, OutType>(in) {}

  explicit BruskovaVImageSmoothingMPI(const ppc::TaskData &data) : ppc::Task<InType, OutType>(data) {}

  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  ppc::TaskType GetTaskType() const override {
    return ppc::TaskType::TASK;
  }

 private:
  std::vector<int> input_img_;
  std::vector<int> result_img_;
  int width_ = 0, height_ = 0;
};

}  // namespace bruskova_v_image_smoothing
