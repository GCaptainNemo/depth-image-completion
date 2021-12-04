cmake_minimum_required(VERSION 3.3.1)

project(range_img_complete)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

add_library(range_img_complete src/range_img_complete.cpp)

add_executable(demo src/demo.cpp)

target_link_libraries(demo range_img_complete ${OpenCV_LIBRARIES})
