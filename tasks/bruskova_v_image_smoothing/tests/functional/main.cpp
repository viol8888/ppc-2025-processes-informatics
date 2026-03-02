#include <gtest/gtest.h>
#include <tuple>
#include <vector>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
#include "bruskova_v_image_smoothing/mpi/include/ops_mpi.hpp"
#include "bruskova_v_image_smoothing/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"

namespace bruskova_v_image_smoothing {

class BruskovaVImageSmoothingFuncTests : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
 protected:
  void SetUp() override {
    auto test_params = std::get<static_cast<std::size_t>(ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    
    int size = std::get<0>(test_params);
    input_data_ = std::vector<int>(size, 128);
    expected_output_ = std::vector<int>(size, 128);
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return output_data.size() == input_data_.size();
  }

 private:
  InType input_data_;
};

TEST_P(BruskovaVImageSmoothingFuncTests, SmoothingTest) {
  ExecuteTest(GetParam());
}

const std::vector<TestType> kTestParam = {std::make_tuple(10), std::make_tuple(50)};

const auto kTestTasksList = std::tuple_cat(
    ppc::util::AddFuncTask<BruskovaVImageSmoothingMPI, InType, OutType, TestType>(kTestParam, "bruskova_v_image_smoothing_mpi"),
    ppc::util::AddFuncTask<BruskovaVImageSmoothingSEQ, InType, OutType, TestType>(kTestParam, "bruskova_v_image_smoothing_seq"));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);

INSTANTIATE_TEST_SUITE_P(FuncTests, BruskovaVImageSmoothingFuncTests, kGtestValues,
                         BruskovaVImageSmoothingFuncTests::PrintFuncTestName<BruskovaVImageSmoothingFuncTests>);

}  // namespace bruskova_v_image_smoothing