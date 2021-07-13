cmake_minimum_required(VERSION 3.0.0)
project(Non-DivisibleSubset VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Non-DivisibleSubset main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
