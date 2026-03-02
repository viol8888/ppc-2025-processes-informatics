#include <gtest/gtest.h>

#include <vector>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
#include "bruskova_v_image_smoothing/mpi/include/ops_mpi.hpp"
#include "bruskova_v_image_smoothing/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace bruskova_v_image_smoothing {
class ImageSmoothingPerfTests
    : public ppc::util::BaseRunPerfTests<InType, OutType> {
protected:
  void SetUp() override { input_data_ = std::vector<int>(1000, 128); }
  bool CheckTestOutputData(OutType &output_data) final {
    return output_data.size() == input_data_.size();
  }
  InType GetTestInputData() final { return input_data_; }

private:
  InType input_data_;
};

TEST_P(ImageSmoothingPerfTests, RunPerf) { ExecuteTest(GetParam()); }

const auto kAllPerfTasks =
    ppc::util::MakeAllPerfTasks<InType, BruskovaVImageSmoothingMPI,
                                BruskovaVImageSmoothingSEQ>(
        PPC_SETTINGS_bruskova_v_image_smoothing);
const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);
INSTANTIATE_TEST_SUITE_P(PerfTests, ImageSmoothingPerfTests, kGtestValues,
                         ImageSmoothingPerfTests::CustomPerfTestName);
} // namespace bruskova_v_image_smoothing
