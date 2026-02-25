#include <gtest/gtest.h>
#include <vector>
#include <tuple>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
#include "bruskova_v_image_smoothing/mpi/include/ops_mpi.hpp"
#include "bruskova_v_image_smoothing/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"

namespace bruskova_v_image_smoothing {

class BruskovaVImageSmoothingFuncTests : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
 public:
  BruskovaVImageSmoothingFuncTests() = default;

 protected:
  void SetUp() override {
    TestType params = std::get<static_cast<std::size_t>(ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    input_data_ = std::get<0>(params);
    expected_output_ = std::get<1>(params);
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return output_data == expected_output_;
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 private:
  InType input_data_;
  OutType expected_output_;
};

TEST_P(BruskovaVImageSmoothingFuncTests, TestImageSmoothing) {
  ExecuteTest(GetParam());
}

const std::vector<TestType> kTestParam = {

    std::make_tuple(std::make_pair(std::vector<int>(9, 255), std::make_pair(3, 3)), std::vector<int>(9, 255)),
    
    std::make_tuple(
        std::make_pair(std::vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90}, std::make_pair(3, 3)),
        std::vector<int>{30, 35, 40, 45, 50, 55, 60, 65, 70}
    ),

    std::make_tuple(std::make_pair(std::vector<int>{10, 20, 30, 40}, std::make_pair(2, 2)), 
                    std::vector<int>{25, 25, 25, 25})
};

const auto kTestTasksList =
    std::tuple_cat(ppc::util::AddFuncTask<BruskovaVImageSmoothingMPI, InType>(kTestParam, PPC_SETTINGS_bruskova_v_image_smoothing),
                   ppc::util::AddFuncTask<BruskovaVImageSmoothingSEQ, InType>(kTestParam, PPC_SETTINGS_bruskova_v_image_smoothing));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);

INSTANTIATE_TEST_SUITE_P(ImageSmoothingTests, BruskovaVImageSmoothingFuncTests, kGtestValues);

}  // namespace bruskova_v_image_smoothing