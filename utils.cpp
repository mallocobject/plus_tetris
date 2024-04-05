#include "utils.h"

int utils::getFPS()
{
    static auto begin = std::chrono::steady_clock::now();
    static int frame_count_buff = 0;
    static int frame_count = 0;

    auto end = std::chrono::steady_clock::now();
    frame_count_buff++;
    if (end - begin > 1s)
    {
        frame_count = frame_count_buff;
        frame_count_buff = 0;
        begin = end;
    }
    terminal::setCursor(1, 1);
    terminal::setColor(terminal::Color::White, true);
    terminal::write("FPS: ");
    terminal::write(frame_count);
    return frame_count;
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
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

void utils::setDuration(int interval)
{
    static auto begin = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin);

    if (elapsed.count() < interval)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval) - elapsed);
    }

    begin = std::chrono::steady_clock::now();
}

int utils::b2c(int val)
{
    return val * 2 - 1;
}
