#include <gtest/gtest.h>
#include <mpi.h>

#include <array>
#include <cmath>
#include <tuple>
#include <vector>
#include <string>

#include "bruskova_v_global_optimization/common/include/common.hpp"
#include "bruskova_v_global_optimization/mpi/include/ops_mpi.hpp"
#include "bruskova_v_global_optimization/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"

namespace bruskova_v_global_optimization {

class BruskovaVGlobalOptimizationFuncTests : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
 public:
  BruskovaVGlobalOptimizationFuncTests() = default;

  static std::string PrintTestParam(const testing::TestParamInfo<ParamType>& info) {
    return "GlobalOptimizationTest";
  }

 protected:
  void SetUp() override {
    TestType params = std::get<static_cast<std::size_t>(ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    input_data_ = std::get<0>(params);
    expected_output_ = std::get<1>(params);
  }

  bool CheckTestOutputData(OutType &output_data) final {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank != 0) {
      return true;
    }

    if (output_data.size() != expected_output_.size()) {
      return false;
    }
    for (size_t i = 0; i < output_data.size(); ++i) {
      if (std::abs(output_data[i] - expected_output_[i]) > 1e-6) {
        return false;
      }
    }
    return true;
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 private:
  InType input_data_;
  OutType expected_output_;
};

TEST_P(BruskovaVGlobalOptimizationFuncTests, TestOptimization) {
  ExecuteTest(GetParam());
}

const std::array<TestType, 2> kTestParam = {
    TestType{std::vector<double>{-1.0, 1.0, -1.0, 1.0, 0.1}, std::vector<double>{0.0, 0.0, 0.0}},
    TestType{std::vector<double>{1.0, 2.0, 1.0, 2.0, 0.1}, std::vector<double>{2.0, 1.0, 1.0}}};

const auto kTestTasksList = std::tuple_cat(
    ppc::util::AddFuncTask<BruskovaVGlobalOptimizationMPI, InType>(kTestParam, "bruskova_v_global_optimization_mpi"),
    ppc::util::AddFuncTask<BruskovaVGlobalOptimizationSEQ, InType>(kTestParam, "bruskova_v_global_optimization_seq"));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);

INSTANTIATE_TEST_SUITE_P(OptimizationTests, BruskovaVGlobalOptimizationFuncTests, kGtestValues,
                         BruskovaVGlobalOptimizationFuncTests::PrintFuncTestName<BruskovaVGlobalOptimizationFuncTests>);

}  // namespace bruskova_v_global_optimization