#pragma once

// 引入所需的头文件
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <unordered_map>
#include <map>
#include <mutex>
#include <functional>
#include <windows.h>
#include <vector>
#include <array>
#include <string>
#include <utility>
#include <conio.h>
#include <random>
#include <cassert>
#include <limits>
#include "utils.h"
#include "terminal.h"
#include "tetromino.h"

// 定义键盘按键状态宏
#define KEY_UP(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0 : 1)
#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0)

// 使用C++14的字面量运算符，可以直接使用时间单位，如1s、1ms等
using namespace std::chrono_literals;

// 定义矩阵类型，用于表示游戏区域
using Matrix = std::vector<std::vector<int>>;
using Matrix_ref = std::vector<std::vector<int>> &;

// 定义俄罗斯方块类型，每个方块由4x4的数组表示，数组中的每个元素是一个坐标对
using Tetromino = std::array<std::array<std::pair<int, int>, 4>, 4>;
using Tetromino_ref = std::array<std::array<std::pair<int, int>, 4>, 4> &;