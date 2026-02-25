#include "../include/ops_seq.hpp"

namespace bruskova_v_image_smoothing {

BruskovaVImageSmoothingSEQ::BruskovaVImageSmoothingSEQ(const InType &in) : BaseTask(in) {}

bool BruskovaVImageSmoothingSEQ::ValidationImpl() {
  
  return std::get<1>(this->in_) >= 3 && std::get<2>(this->in_) >= 3;
}

bool BruskovaVImageSmoothingSEQ::PreProcessingImpl() {
  input_img_ = std::get<0>(this->in_);
  width_ = std::get<1>(this->in_);
  height_ = std::get<2>(this->in_);
  result_img_ = input_img_;
  return true;
}

bool BruskovaVImageSmoothingSEQ::RunImpl() {
  for (int y = 1; y < height_ - 1; y++) {
    for (int x = 1; x < width_ - 1; x++) {
      int sum = 0;
      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          sum += input_img_[(y + dy) * width_ + (x + dx)];
        }
      }
      result_img_[y * width_ + x] = sum / 9;
    }
  }
  return true;
}

bool BruskovaVImageSmoothingSEQ::PostProcessingImpl() {
  this->out_ = result_img_;
  return true;
}

}  // namespace bruskova_v_image_smoothing