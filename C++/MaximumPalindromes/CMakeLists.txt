cmake_minimum_required(VERSION 3.0.0)
project(MaximumPalindromes VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(MaximumPalindromes main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input27.txt
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
