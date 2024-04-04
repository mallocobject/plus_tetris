cmake_minimum_required(VERSION 3.25)

project(plus_tetris)

set(CMAKE_CXX_STANDARD 20)

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})