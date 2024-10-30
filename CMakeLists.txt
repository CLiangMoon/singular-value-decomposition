cmake_minimum_required(VERSION 3.10)

project(SVD_COMPRSS_IMAGE)

set(CMAKE_BUILD_TYPE "Debug")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_DIRS})

add_executable(compress_image main.cpp)

target_link_libraries(compress_image ${OpenCV_LIBS})