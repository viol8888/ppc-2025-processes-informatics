#include "bruskova_v_global_optimization/mpi/include/ops_mpi.hpp"

#include <mpi.h>

#include <algorithm>
#include <limits>
#include <vector>

namespace bruskova_v_global_optimization {

bool BruskovaVGlobalOptimizationMPI::ValidationImpl() {
  return taskData->inputs_count[0] == 5;
}

bool BruskovaVGlobalOptimizationMPI::PreProcessingImpl() {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    auto *in = reinterpret_cast<double *>(taskData->inputs[0]);
    x_min_ = in[0];
    x_max_ = in[1];
    y_min_ = in[2];
    y_max_ = in[3];
    step_ = in[4];
  }
  result_ = {std::numeric_limits<double>::max(), 0.0, 0.0};
  return true;
}

bool BruskovaVGlobalOptimizationMPI::RunImpl() {
  int size = 0, rank = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  double params[5] = {x_min_, x_max_, y_min_, y_max_, step_};
  MPI_Bcast(params, 5, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank != 0) {
    x_min_ = params[0];
    x_max_ = params[1];
    y_min_ = params[2];
    y_max_ = params[3];
    step_ = params[4];
  }

  int total_steps = static_cast<int>((x_max_ - x_min_) / step_) + 1;
  int local_steps = total_steps / size;
  int remainder = total_steps % size;
  int start_step = (rank * local_steps) + (rank < remainder ? rank : remainder);
  int my_steps = local_steps + (rank < remainder ? 1 : 0);

  double local_min[3] = {std::numeric_limits<double>::max(), 0.0, 0.0};
  for (int i = 0; i < my_steps; ++i) {
    double x = x_min_ + (start_step + i) * step_;
    for (double y = y_min_; y <= y_max_; y += step_) {
      double val = (x * x) + (y * y);
      if (val < local_min[0]) {
        local_min[0] = val;
        local_min[1] = x;
        local_min[2] = y;
      }
    }
  }

  if (rank == 0) {
    result_ = {local_min[0], local_min[1], local_min[2]};
    for (int p = 1; p < size; ++p) {
      double recv_min[3];
      MPI_Recv(recv_min, 3, MPI_DOUBLE, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      if (recv_min[0] < result_[0]) {
        result_[0] = recv_min[0];
        result_[1] = recv_min[1];
        result_[2] = recv_min[2];
      }
    }
  } else {
    MPI_Send(local_min, 3, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  return true;
}

bool BruskovaVGlobalOptimizationMPI::PostProcessingImpl() {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    auto *out = reinterpret_cast<double *>(taskData->outputs[0]);
    out[0] = result_[0];
    out[1] = result_[1];
    out[2] = result_[2];
  }
  return true;
}
}  // namespace bruskova_v_global_optimization

