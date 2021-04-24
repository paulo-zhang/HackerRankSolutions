cmake_minimum_required(VERSION 3.0.0)
project(Candies VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Candies main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input01.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

     file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input07.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})