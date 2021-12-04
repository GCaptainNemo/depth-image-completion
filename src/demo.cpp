#include "range_img_complete.h"
#include <iostream>
#include <string>



void toColorImage(const cv::Mat &r_img, cv::Mat &color_img)
{
    cv::Mat normalize_dense_r_img;
    cv::normalize(r_img, normalize_dense_r_img, 1.0, 0, cv::NORM_MINMAX);
    cv::Mat dense_r_image_8uc1;
    normalize_dense_r_img.convertTo(dense_r_image_8uc1, CV_8UC1,255.0);
    cv::applyColorMap(dense_r_image_8uc1, color_img, cv::COLORMAP_JET);
}


void matread(const std::string &filename, cv::Mat &read_mat)
{
    int rows, cols, data, depth, type, channels;
    std::ifstream file (filename, std::fstream::binary);
    if (!file.is_open())
        return;
    try {
        std::cout << "size of int = " << sizeof(int) << std::endl;
        file.read(reinterpret_cast<char *>(&rows), sizeof(rows));
        file.read(reinterpret_cast<char *>(&cols), sizeof(cols));
        file.read(reinterpret_cast<char *>(&depth), sizeof(depth));
        file.read(reinterpret_cast<char *>(&type), sizeof(type));
        file.read(reinterpret_cast<char *>(&channels), sizeof(channels));
        file.read(reinterpret_cast<char *>(&data), sizeof(data));
        std::cout << "rows = " << rows << "cols = " << cols << "type = " << type << "channels = " << channels << std::endl; 
        read_mat = cv::Mat(rows, cols, type);
        file.read(reinterpret_cast<char *>(read_mat.data), data);
    } catch (...) {
        file.close();
        return;
    }
    file.close();

}


int main(int argc, char **argv)
{
    // dense img complete
    std::string file_dir;
    std::cout << "argc = " << argc;
    if (argc == 1){
        file_dir = "../resources/raw_range_img.bin";
    }
    else if(argc > 1)
    {
        file_dir = argv[1];
    }
    std::string blur_type = std::string("gaussian");
    bool extrapolate = true;
    cv::Mat dense_range_img;
    // cv::Mat range_img = cv::imread(file_dir, -1);
    cv::Mat range_img;
    matread(file_dir, range_img);   
    range_image_complete(range_img, dense_range_img, extrapolate, blur_type);

    // color map
    cv::Mat color_dense_range_img;
    cv::Mat color_range_img;   
    toColorImage(range_img, color_range_img);
    toColorImage(dense_range_img, color_dense_range_img);

    // show
    std::vector<cv::Mat> hImg;
    hImg.push_back(color_range_img);
    hImg.push_back(color_dense_range_img);
    cv::Mat cat_img;
    cv::vconcat(hImg, cat_img);
    cv::imshow("src", cat_img);
    cv::waitKey(0); 
    return 0;

}
