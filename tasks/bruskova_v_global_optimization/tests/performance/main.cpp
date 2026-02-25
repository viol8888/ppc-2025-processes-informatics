#include <gtest/gtest.h>
#include <vector>

#include "bruskova_v_global_optimization/common/include/common.hpp"
#include "bruskova_v_global_optimization/mpi/include/ops_mpi.hpp"
#include "bruskova_v_global_optimization/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace bruskova_v_global_optimization {

class BruskovaVGlobalOptimizationPerfTests : public ppc::util::BaseRunPerfTests<InType, OutType> {
 private:
  InType input_data_;
  OutType expected_output_;

  void SetUp() override {
    
    input_data_ = {-50.0, 50.0, -50.0, 50.0, 0.002};
    expected_output_ = {0.0, 0.0, 0.0};
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return std::abs(output_data[0] - expected_output_[0]) < 1e-6;
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 public:
  BruskovaVGlobalOptimizationPerfTests() = default;
};

TEST_P(BruskovaVGlobalOptimizationPerfTests, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks =
    ppc::util::MakeAllPerfTasks<InType, BruskovaVGlobalOptimizationMPI, BruskovaVGlobalOptimizationSEQ>(PPC_SETTINGS_bruskova_v_global_optimization);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);

INSTANTIATE_TEST_SUITE_P(RunModeTests, BruskovaVGlobalOptimizationPerfTests, kGtestValues);

}  // namespace bruskova_v_global_optimization