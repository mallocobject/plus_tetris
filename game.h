#pragma once

#include "define.h"
#include "tetromino.h"

using Tetromino_ref = std::array<std::array<std::pair<int, int>, 4>, 4> &;

struct Game
{
public:
    static void start();
    static void update(int &top);
    static void render(Tetromino_ref matrix, int top, int left, int index);
    static void end();
    static std::thread runSubThread();
    static void setFPS(int fps);
    static void setDuration(int interval);
    static void setWindow(int top, int left, int height, int width, const std::string &title);
    static void rotate(int &index);
    static void down(int &top);
    static void left(int &left);
    static void right(int &left);

    static std::atomic<bool> running_flag;

private:
    static void handleSignals(std::unordered_map<char, std::function<void()>> &key_map);
};
