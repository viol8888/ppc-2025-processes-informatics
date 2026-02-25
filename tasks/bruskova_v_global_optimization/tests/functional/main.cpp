#include <gtest/gtest.h>
#include <vector>
#include <tuple>

#include "bruskova_v_global_optimization/common/include/common.hpp"
#include "bruskova_v_global_optimization/mpi/include/ops_mpi.hpp"
#include "bruskova_v_global_optimization/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"

namespace bruskova_v_global_optimization {

class BruskovaVGlobalOptimizationFuncTests : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
 public:
  BruskovaVGlobalOptimizationFuncTests() = default;

 protected:
  void SetUp() override {
    TestType params = std::get<static_cast<std::size_t>(ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    input_data_ = std::get<0>(params);
    expected_output_ = std::get<1>(params);
  }

  bool CheckTestOutputData(OutType &output_data) final {
    for (size_t i = 0; i < output_data.size(); ++i) {
        if (std::abs(output_data[i] - expected_output_[i]) > 1e-6) return false;
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

const std::vector<TestType> kTestParam = {
    
    std::make_tuple(std::vector<double>{-1.0, 1.0, -1.0, 1.0, 0.1}, std::vector<double>{0.0, 0.0, 0.0}),
    
    std::make_tuple(std::vector<double>{1.0, 2.0, 1.0, 2.0, 0.1}, std::vector<double>{2.0, 1.0, 1.0})
};

const auto kTestTasksList =
    std::tuple_cat(ppc::util::AddFuncTask<BruskovaVGlobalOptimizationMPI, InType>(kTestParam, PPC_SETTINGS_bruskova_v_global_optimization),
                   ppc::util::AddFuncTask<BruskovaVGlobalOptimizationSEQ, InType>(kTestParam, PPC_SETTINGS_bruskova_v_global_optimization));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);

INSTANTIATE_TEST_SUITE_P(OptimizationTests, BruskovaVGlobalOptimizationFuncTests, kGtestValues);

}  // namespace bruskova_v_global_optimization