cmake_minimum_required(VERSION 3.23)
project(DPI_challenge )

set(CMAKE_CXX_STANDARD 11)


add_executable(DPI_challenge main.cpp)

target_link_libraries(DPI_challenge ${CMAKE_SOURCE_DIR}/miracl.a)