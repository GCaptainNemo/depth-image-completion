#pragma once
#include <opencv2/opencv.hpp>

void range_image_complete(const cv::Mat &sparse_r_img, cv::Mat &dense_r_img, const bool &is_extrapolate, const std::string &blur_type);






