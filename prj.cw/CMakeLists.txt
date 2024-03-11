cmake_minimum_required(VERSION 3.10)
project(DistanceTransform)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(DistanceTransform "DistanceTransform/main.cpp" "DistanceTransform/add.h" "DistanceTransform/add.cpp")
target_link_libraries(DistanceTransform ${OpenCV_LIBS})