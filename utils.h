#pragma once

#include "define.h"

namespace utils
{
    int getFPS(int &frame_count);
    long long getCurrentTimestamp();
    bool checkDuration(int interval);
    int generateRandomNumber(int min, int max);
    void setDuration(int interval);
    int b2c(int val);
    int getScore(int score);
} // namespace utilities