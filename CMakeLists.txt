# 设置构建此项目所需的最低 CMake 版本为 3.25
cmake_minimum_required(VERSION 3.25)

# 定义项目的名称，这里的项目名称是 "plus_tetris"
project(plus_tetris)

# 设置项目使用的 C++ 标准版本为 C++20
set(CMAKE_CXX_STANDARD 20)

# 将当前目录中的所有源文件添加到 `SRC_LIST` 变量中
aux_source_directory(./ SRC_LIST)

# 添加一个可执行文件目标，目标名称为项目名称（这里是 "plus_tetris"），源文件列表为 `SRC_LIST`
add_executable(${PROJECT_NAME} ${SRC_LIST})