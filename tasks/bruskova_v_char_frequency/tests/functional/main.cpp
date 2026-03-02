#include <gtest/gtest.h>
#include <mpi.h>

#include <array>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "bruskova_v_char_frequency/common/include/common.hpp"
#include "bruskova_v_char_frequency/mpi/include/ops_mpi.hpp"
#include "bruskova_v_char_frequency/seq/include/ops_seq.hpp"
#include "util/include/func_test_util.hpp"
#include "util/include/util.hpp"

namespace bruskova_v_char_frequency {

class BruskovaVCharFrequencyFuncTests
    : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
public:
  BruskovaVCharFrequencyFuncTests() = default;

  // Обязательный метод для печати параметров
  static std::string
  PrintTestParam(const testing::TestParamInfo<ParamType> &info) {
    return "CharFreqTest";
  }

protected:
  void SetUp() override {
    TestType params = std::get<static_cast<std::size_t>(
        ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    input_data_ = std::get<0>(params);
    expected_output_ = std::get<1>(params);
  }

  bool CheckTestOutputData(OutType &output_data) final {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank != 0) {
      return true;
    }
    return output_data == expected_output_;
  }

  InType GetTestInputData() final { return input_data_; }

private:
  InType input_data_;
  OutType expected_output_;
};

TEST_P(BruskovaVCharFrequencyFuncTests, TestCharFrequency) {
  ExecuteTest(GetParam());
}

const std::array<TestType, 5> kTestParam = {
    TestType{std::make_pair(std::string("abracadabra"), 'a'), 5},
    TestType{std::make_pair(std::string("hello world"), 'o'), 2},
    TestType{std::make_pair(std::string("aaaaa"), 'b'), 0},
    TestType{std::make_pair(std::string(""), 'x'), 0},
    TestType{std::make_pair(std::string("z"), 'z'), 1}};

// ИСПРАВЛЕНО: Оставлен только один шаблонный аргумент InType
const auto kTestTasksList =
    std::tuple_cat(ppc::util::AddFuncTask<BruskovaVCharFrequencyMPI, InType>(
                       kTestParam, "bruskova_v_char_frequency_mpi"),
                   ppc::util::AddFuncTask<BruskovaVCharFrequencySEQ, InType>(
                       kTestParam, "bruskova_v_char_frequency_seq"));

const auto kGtestValues = ppc::util::ExpandToValues(kTestTasksList);

INSTANTIATE_TEST_SUITE_P(CharFrequencyTests, BruskovaVCharFrequencyFuncTests,
                         kGtestValues,
                         BruskovaVCharFrequencyFuncTests::PrintFuncTestName<
                             BruskovaVCharFrequencyFuncTests>);

} // namespace bruskova_v_char_frequency
