#include <gtest/gtest.h>
#include <mpi.h>

#include <chrono>
#include <iostream>
#include <string>
#include <utility>

#include "bruskova_v_char_frequency/mpi/include/ops_mpi.hpp"
#include "bruskova_v_char_frequency/seq/include/ops_seq.hpp"

namespace bruskova_v_char_frequency {

TEST(BruskovaVCharFrequencyPerfTests, RunManualMPIPerf) {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  std::string giant_str(10000000, 'a');
  InType in = std::make_pair(giant_str, 'a');
  OutType out = 0;

  auto task = std::make_shared<BruskovaVCharFrequencyMPI>(in);

  auto start_time = MPI_Wtime();
  if (task->ValidationImpl()) {
    task->PreProcessingImpl();
    task->RunImpl();
    task->PostProcessingImpl();
  }
  auto end_time = MPI_Wtime();

  if (rank == 0) {
    std::cout << "[ PERF ] MPI Execution Time: " << (end_time - start_time)
              << " seconds\n";
  }
}

TEST(BruskovaVCharFrequencyPerfTests, RunManualSEQPerf) {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    std::string giant_str(10000000, 'a');
    InType in = std::make_pair(giant_str, 'a');
    OutType out = 0;

    auto task = std::make_shared<BruskovaVCharFrequencySEQ>(in);

    auto start_time = std::chrono::high_resolution_clock::now();
    if (task->ValidationImpl()) {
      task->PreProcessingImpl();
      task->RunImpl();
      task->PostProcessingImpl();
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;

    std::cout << "[ PERF ] SEQ Execution Time: " << diff.count()
              << " seconds\n";
  }
}

} // namespace bruskova_v_char_frequency
