set(CMAKE_CXX_COMPILER icpx)
cmake_minimum_required(VERSION 3.4)
project(syclinfo)
set(CMAKE_CXX_FLAGS "-O3 -fsycl")
add_executable(syclinfo  syclinfo.cpp)


