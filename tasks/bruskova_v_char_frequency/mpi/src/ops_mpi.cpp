#include "bruskova_v_char_frequency/mpi/include/ops_mpi.hpp"

#include <mpi.h>

#include <algorithm>
#include <string>
#include <vector>

namespace bruskova_v_char_frequency {

bool BruskovaVCharFrequencyMPI::ValidationImpl() {
  return taskData->inputs_count[0] > 0 && taskData->outputs_count[0] == 1;
}

bool BruskovaVCharFrequencyMPI::PreProcessingImpl() {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    auto *input_ptr = reinterpret_cast<char *>(taskData->inputs[0]);
    this->GetInput().first = std::string(input_ptr, taskData->inputs_count[0]);
    this->GetInput().second = *reinterpret_cast<char *>(taskData->inputs[1]);
    target_char_ = this->GetInput().second;
  }
  return true;
}

bool BruskovaVCharFrequencyMPI::RunImpl() {
  int size = 0;
  int rank = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int total_len = 0;
  if (rank == 0) {
    total_len = static_cast<int>(this->GetInput().first.length());
  }

  MPI_Bcast(&total_len, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&target_char_, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

  int base_len = total_len / size;
  int remainder = total_len % size;
  int local_len = base_len + (rank < remainder ? 1 : 0);
  int start_pos = (rank * base_len) + (rank < remainder ? rank : remainder);

  std::vector<char> local_str(local_len);
  if (rank == 0) {
    for (int i = 1; i < size; ++i) {
      int i_local_len = base_len + (i < remainder ? 1 : 0);
      int i_start_pos = (i * base_len) + (i < remainder ? i : remainder);
      MPI_Send(this->GetInput().first.data() + i_start_pos, i_local_len, MPI_CHAR, i, 0, MPI_COMM_WORLD);
    }
    std::copy(this->GetInput().first.begin(), this->GetInput().first.begin() + local_len, local_str.begin());
  } else if (local_len > 0) {
    MPI_Recv(local_str.data(), local_len, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  int local_count = static_cast<int>(std::count(local_str.begin(), local_str.end(), target_char_));
  MPI_Reduce(&local_count, &result_count_, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  return true;
}

bool BruskovaVCharFrequencyMPI::PostProcessingImpl() {
  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    reinterpret_cast<int *>(taskData->outputs[0])[0] = result_count_;
  }
  return true;
}

}  // namespace bruskova_v_char_frequency
