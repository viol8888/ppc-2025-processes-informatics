#include <gtest/gtest.h>
#include <string>

#include "bruskova_v_char_frequency/common/include/common.hpp"
#include "bruskova_v_char_frequency/mpi/include/ops_mpi.hpp"
#include "bruskova_v_char_frequency/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"
#include "util/include/util.hpp"

namespace bruskova_v_char_frequency {

class BruskovaVCharFrequencyPerfTests : public ppc::util::BaseRunPerfTests<InType, OutType> {
 private:
  InType input_data_;
  OutType expected_output_ = 0;

  void SetUp() override {

    std::string giant_str(20000000, 'b');
    for(size_t i = 0; i < giant_str.size(); i += 2) {
        giant_str[i] = 'a';
    }
    
    input_data_ = std::make_pair(giant_str, 'a');
    expected_output_ = 10000000;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return output_data == expected_output_;
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 public:
  BruskovaVCharFrequencyPerfTests() = default;
};

TEST_P(BruskovaVCharFrequencyPerfTests, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks =
    ppc::util::MakeAllPerfTasks<InType, BruskovaVCharFrequencyMPI, BruskovaVCharFrequencySEQ>(PPC_SETTINGS_bruskova_v_char_frequency);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);

INSTANTIATE_TEST_SUITE_P(RunModeTests, BruskovaVCharFrequencyPerfTests, kGtestValues);

}  // namespace bruskova_v_char_frequency