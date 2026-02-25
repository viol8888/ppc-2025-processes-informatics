#include <gtest/gtest.h>
#include <tuple>
#include <vector>

#include "bruskova_v_char_frequency/common/include/common.hpp"
#include "bruskova_v_char_frequency/mpi/include/ops_mpi.hpp"
#include "bruskova_v_char_frequency/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"
#include "util/include/util.hpp"

namespace bruskova_v_char_frequency {

class BruskovaVCharFrequencyFuncTests : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
 public:
  BruskovaVCharFrequencyFuncTests() = default;

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
  OutType expected_output_ = 0;
};

TEST_P(BruskovaVCharFrequencyFuncTests, TestCharFrequency) {
  ExecuteTest(GetParam());
}

const std::vector<TestType> kTestParam = {
    std::make_tuple(std::make_pair("abracadabra", 'a'), 5),
    std::make_tuple(std::make_pair("hello world", 'o'), 2),
    std::make_tuple(std::make_pair("aaaaa", 'b'), 0),
    std::make_tuple(std::make_pair("", 'x'), 0),
    std::make_tuple(std::make_pair("z", 'z'), 1)
};

const auto kTestTasksList =
    std::tuple_cat(ppc::util::AddFuncTask<BruskovaVCharFrequencyMPI, InType>(kTestParam, PPC_SETTINGS_bruskova_v_char_frequency),
                   ppc::util::AddFuncTask<BruskovaVCharFrequencySEQ, InType>(kTestParam, PPC_SETTINGS_bruskova_v_char_frequency));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);

INSTANTIATE_TEST_SUITE_P(CharFrequencyTests, BruskovaVCharFrequencyFuncTests, kGtestValues);

}  // namespace bruskova_v_char_frequency