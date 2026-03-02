#include <gtest/gtest.h>
#include <mpi.h>

#include <iostream>
#include <vector>

#include "bruskova_v_global_optimization/common/include/common.hpp"
#include "bruskova_v_global_optimization/mpi/include/ops_mpi.hpp"

namespace bruskova_v_global_optimization {

TEST(BruskovaVGlobalOptimizationPerfTests, RunManualMPI) {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  InType in = {-100.0, 100.0, -100.0, 100.0, 0.05};
  BruskovaVGlobalOptimizationMPI task(in);

  double start = MPI_Wtime();
  if (task.Validation()) {
    task.PreProcessing();
    task.Run();
    task.PostProcessing();
  }
  double end = MPI_Wtime();

  if (rank == 0) {
    std::cout << "[ PERF ] Global Optimization MPI Time: " << (end - start) << " seconds\n";
  }
}
}  // namespace bruskova_v_global_optimization

