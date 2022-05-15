cmake_minimum_required(VERSION 3.10)

project(memo
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(gtest)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/gtest.cmake)

include_directories(src)
add_subdirectory(src)
