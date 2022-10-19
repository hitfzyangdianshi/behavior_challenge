cmake_minimum_required(VERSION 3.23)
project(DPI_challenge )

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include_miracl)

add_executable(DPI_challenge main.cpp interposition/jfree.c interposition/jmalloc.c)

target_link_libraries(DPI_challenge ${CMAKE_SOURCE_DIR}/lib_miracl/miracl.a)