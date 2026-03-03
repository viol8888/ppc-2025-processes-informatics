#include <gtest/gtest.h>
#include <mpi.h>

#include <iostream>
#include <tuple>
#include <vector>

#include "bruskova_v_image_smoothing/common/include/common.hpp"
#include "bruskova_v_image_smoothing/mpi/include/ops_mpi.hpp"

namespace bruskova_v_image_smoothing {

TEST(BruskovaVImageSmoothingPerfTests, RunManualMPI) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int w = 2000;
  int h = 2000;
  std::vector<int> img(w * h, 128);
  InType in = std::make_tuple(img, w, h);

  BruskovaVImageSmoothingMPI task(in);

  double start = MPI_Wtime();
  if (task.Validation()) {
    task.PreProcessing();
    task.Run();
    task.PostProcessing();
  }
  double end = MPI_Wtime();

  if (rank == 0) {
    std::cout << "[ PERF ] Image Smoothing MPI Time: " << (end - start) << " seconds" << std::endl;
  }
}

}  // namespace bruskova_v_image_smoothing
