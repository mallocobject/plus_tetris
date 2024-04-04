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
#include <string>
#include <utility>
#include <conio.h>
#include <random>
#include "utils.h"
#include "terminal.h"
#include "game.h"

#define KEY_UP(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 0 : 1)
#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0)

using namespace std::chrono_literals;