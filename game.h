#pragma once

#include "define.h"

struct Game
{
    static void start();
    static void update();
    static void render();
    static void end();
    static std::thread runSubThread();
    static void setFPS(int fps);
    static void setDuration(int interval);
    static void setWindow(int row, int col, int height, int width, const std::string &title);
};
