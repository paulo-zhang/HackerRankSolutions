cmake_minimum_required(VERSION 3.0.0)
project(Abbreviation VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Abbreviation main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input14.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input12.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(CPack)
