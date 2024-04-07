#include "utils.h"

int utils::getFPS(int &frame_count)
{
    static auto begin = std::chrono::steady_clock::now();
    static int fps = 0;

    auto end = std::chrono::steady_clock::now();
    if (end - begin >= 1s)
    {
        fps = frame_count;
        frame_count = 0;
        begin = end;
    }
    terminal::reset();
    terminal::setCursor(1, 7);
    terminal::setColor(terminal::Color::White, true);
    terminal::write(fps);
    terminal::write(' ');
    return fps;
}

long long utils::getCurrentTimestamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

bool utils::checkDuration(int interval)
{
    static auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    if (end - begin > std::chrono::milliseconds(interval))
    {
        begin = end;
        return true;
    }
    return false;
}

int utils::generateRandomNumber(int min, int max)
{
    // 使用当前时间作为种子
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

void utils::setDuration(int interval)
{
    auto begin = std::chrono::system_clock::now();
    auto now = begin;
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
    while (duration.count() < interval)
    {
        now = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);
    }
}

// void timingus(size_t us)
// {
//     auto start = std::chrono::system_clock::now();
//     while (1)
//     {
//         auto end = std::chrono::system_clock::now();
//         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//         if (duration.count() > us) break;
//     }
// }

int utils::b2c(int val)
{
    return val * 2 - 1;
}

int utils::getScore(int score)
{
    terminal::reset();
    terminal::setCursor(3, 9);
    terminal::setColor(terminal::Color::White, true);
    terminal::write(score);
    return score;
}
