#pragma once

#include "define.h"

namespace utilities
{
    int getFPS();
    long long getCurrentTimestamp();
    bool setDuration(int interval);
    int generateRandomNumber(int min, int max);
} // namespace utilities