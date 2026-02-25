#include <gtest/gtest.h>
#include <vector>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
#include "bruskova_v_image_smoothing/mpi/include/ops_mpi.hpp"
#include "bruskova_v_image_smoothing/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace bruskova_v_image_smoothing {

class BruskovaVImageSmoothingPerfTests : public ppc::util::BaseRunPerfTests<InType, OutType> {
 private:
  InType input_data_;
  OutType expected_output_;

  void SetUp() override {
    int w = 2000, h = 2000;
    std::vector<int> img(w * h, 128);
    input_data_ = std::make_tuple(img, w, h);
    expected_output_ = img; 
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return output_data == expected_output_;
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 public:
  BruskovaVImageSmoothingPerfTests() = default;
};

TEST_P(BruskovaVImageSmoothingPerfTests, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks =
    ppc::util::MakeAllPerfTasks<InType, BruskovaVImageSmoothingMPI, BruskovaVImageSmoothingSEQ>(PPC_SETTINGS_bruskova_v_image_smoothing);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);

INSTANTIATE_TEST_SUITE_P(RunModeTests, BruskovaVImageSmoothingPerfTests, kGtestValues);

}  // namespace bruskova_v_image_smoothing