#pragma once

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

#define KEY_UP(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0 : 1)
#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0)

using namespace std::chrono_literals;

using Matrix = std::vector<std::vector<int>>;
using Matrix_ref = std::vector<std::vector<int>> &;
using Tetromino = std::array<std::array<std::pair<int, int>, 4>, 4>;
using Tetromino_ref = std::array<std::array<std::pair<int, int>, 4>, 4> &;