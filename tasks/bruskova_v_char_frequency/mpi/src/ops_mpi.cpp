#include "../include/ops_mpi.hpp"

namespace bruskova_v_char_frequency {

BruskovaVCharFrequencyMPI::BruskovaVCharFrequencyMPI(const InType &in) : BaseTask(in) {}

bool BruskovaVCharFrequencyMPI::ValidationImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if (rank == 0) {
    return !this->in_.first.empty();
  }
  return true;
}

bool BruskovaVCharFrequencyMPI::PreProcessingImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    input_str_ = this->in_.first;
    target_char_ = this->in_.second;
  }
  result_count_ = 0;
  return true;
}

bool BruskovaVCharFrequencyMPI::RunImpl() {
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int total_len = 0;
  if (rank == 0) {
    total_len = input_str_.length();
  }
  
  MPI_Bcast(&total_len, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&target_char_, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

  int base_len = total_len / size;
  int remainder = total_len % size;
  int local_len = (rank < remainder) ? (base_len + 1) : base_len;
  int start_pos = rank * base_len + (rank < remainder ? rank : remainder);

  if (rank != 0) {
    input_str_.resize(total_len);
  }
  MPI_Bcast(input_str_.data(), total_len, MPI_CHAR, 0, MPI_COMM_WORLD);

  int local_count = 0;
  for (int i = 0; i < local_len; i++) {
    if (input_str_[start_pos + i] == target_char_) {
      local_count++;
    }
  }

  MPI_Reduce(&local_count, &result_count_, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  return true;
}

bool BruskovaVCharFrequencyMPI::PostProcessingImpl() {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    this->out_ = result_count_;
  }
  return true;
}

}  // namespace bruskova_v_char_frequency