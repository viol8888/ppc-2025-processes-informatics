#include "../include/ops_mpi.hpp"
#include <limits>

namespace bruskova_v_global_optimization {

BruskovaVGlobalOptimizationMPI::BruskovaVGlobalOptimizationMPI(const InType &in) : BaseTask(in) {}

bool BruskovaVGlobalOptimizationMPI::ValidationImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    return this->in_.size() == 5 && this->in_[4] > 0;
  }
  return true;
}

bool BruskovaVGlobalOptimizationMPI::PreProcessingImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    x_min_ = this->in_[0];
    x_max_ = this->in_[1];
    y_min_ = this->in_[2];
    y_max_ = this->in_[3];
    step_  = this->in_[4];
  }
  result_ = {std::numeric_limits<double>::max(), 0.0, 0.0};
  return true;
}

bool BruskovaVGlobalOptimizationMPI::RunImpl() {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  double meta[5];
  if (rank == 0) {
    meta[0] = x_min_; meta[1] = x_max_;
    meta[2] = y_min_; meta[3] = y_max_; meta[4] = step_;
  }
  MPI_Bcast(meta, 5, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  x_min_ = meta[0]; x_max_ = meta[1];
  y_min_ = meta[2]; y_max_ = meta[3]; step_  = meta[4];

  int total_x_steps = (x_max_ - x_min_) / step_;
  int base_steps = total_x_steps / size;
  int remainder = total_x_steps % size;

  int local_steps = (rank < remainder) ? (base_steps + 1) : base_steps;
  int start_step = rank * base_steps + (rank < remainder ? rank : remainder);

  double local_x_min = x_min_ + start_step * step_;
  double local_res[3] = {std::numeric_limits<double>::max(), 0.0, 0.0};

  for (int i = 0; i < local_steps; ++i) {
    double x = local_x_min + i * step_;
    for (double y = y_min_; y <= y_max_; y += step_) {
      double val = x * x + y * y;
      if (val < local_res[0]) {
        local_res[0] = val;
        local_res[1] = x;
        local_res[2] = y;
      }
    }
  }

  std::vector<double> global_res;
  if (rank == 0) {
    global_res.resize(size * 3);
  }

  MPI_Gather(local_res, 3, MPI_DOUBLE, global_res.data(), 3, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    for (int i = 0; i < size; ++i) {
      if (global_res[i * 3] < result_[0]) {
        result_[0] = global_res[i * 3];
        result_[1] = global_res[i * 3 + 1];
        result_[2] = global_res[i * 3 + 2];
      }
    }
  }

  return true;
}

bool BruskovaVGlobalOptimizationMPI::PostProcessingImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    this->out_ = result_;
  }
  return true;
}

}  // namespace bruskova_v_global_optimization