#include "../include/ops_mpi.hpp"

namespace bruskova_v_image_smoothing {

BruskovaVImageSmoothingMPI::BruskovaVImageSmoothingMPI(const InType &in) : BaseTask(in) {}

bool BruskovaVImageSmoothingMPI::ValidationImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    return std::get<1>(this->in_) >= 3 && std::get<2>(this->in_) >= 3;
  }
  return true;
}

bool BruskovaVImageSmoothingMPI::PreProcessingImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    input_img_ = std::get<0>(this->in_);
    width_ = std::get<1>(this->in_);
    height_ = std::get<2>(this->in_);
  }
  return true;
}

bool BruskovaVImageSmoothingMPI::RunImpl() {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int meta[2];
  if (rank == 0) {
    meta[0] = width_;
    meta[1] = height_;
  }
  MPI_Bcast(meta, 2, MPI_INT, 0, MPI_COMM_WORLD);
  width_ = meta[0];
  height_ = meta[1];

  if (rank != 0) {
    input_img_.resize(width_ * height_);
  }
  MPI_Bcast(input_img_.data(), width_ * height_, MPI_INT, 0, MPI_COMM_WORLD);

  int num_rows = height_ - 2;
  if (num_rows <= 0) {
      if (rank == 0) result_img_ = input_img_;
      return true;
  }

  int base_rows = num_rows / size;
  int remainder = num_rows % size;
  int local_rows = (rank < remainder) ? (base_rows + 1) : base_rows;
  int start_row = 1 + rank * base_rows + (rank < remainder ? rank : remainder);

  std::vector<int> local_output(local_rows * width_);
  local_output.assign(input_img_.begin() + start_row * width_, input_img_.begin() + (start_row + local_rows) * width_);

  for (int y = 0; y < local_rows; y++) {
    int global_y = start_row + y;
    for (int x = 1; x < width_ - 1; x++) {
      int sum = 0;
      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          sum += input_img_[(global_y + dy) * width_ + (x + dx)];
        }
      }
      local_output[y * width_ + x] = sum / 9;
    }
  }

  std::vector<int> recvcounts(size);
  std::vector<int> displs(size);
  
  int current_displ = 0;
  for (int i = 0; i < size; i++) {
    int r_rows = (i < remainder) ? (base_rows + 1) : base_rows;
    recvcounts[i] = r_rows * width_;
    displs[i] = current_displ;
    current_displ += recvcounts[i];
  }

  if (rank == 0) {
    result_img_ = input_img_;
  }

  std::vector<int> gather_buffer;
  if (rank == 0) gather_buffer.resize(num_rows * width_);
  
  MPI_Gatherv(local_output.data(), local_rows * width_, MPI_INT, 
              gather_buffer.data(), recvcounts.data(), displs.data(), MPI_INT, 
              0, MPI_COMM_WORLD);

  if (rank == 0) {
    for(int i = 0; i < num_rows * width_; i++) {
      result_img_[width_ + i] = gather_buffer[i];
    }
  }

  return true;
}

bool BruskovaVImageSmoothingMPI::PostProcessingImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    this->out_ = result_img_;
  }
  return true;
}

}  // namespace bruskova_v_image_smoothing