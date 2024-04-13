#include "utils.h" // 引入utils头文件

// 获取当前的帧率，参数frame_count是一个引用，可能会被函数修改
int utils::getFPS(int &frame_count)
{
    static auto begin = std::chrono::steady_clock::now(); // 开始时间
    static int fps = 0;                                   // 帧率

    auto end = std::chrono::steady_clock::now(); // 结束时间
    if (end - begin >= 1s)                       // 如果时间间隔大于等于1秒
    {
        fps = frame_count; // 更新帧率
        frame_count = 0;   // 重置帧数
        begin = end;       // 更新开始时间
    }
    terminal::reset();                                // 重置终端
    terminal::setCursor(18, 49);                      // 设置光标位置
    terminal::setColor(terminal::Color::White, true); // 设置颜色
    terminal::write(fps);                             // 输出帧率
    terminal::write(' ');                             // 输出空格
    return fps;                                       // 返回帧率
}

// 获取当前的时间戳，返回值是一个长整型
long long utils::getCurrentTimestamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

// 检查给定的间隔时间是否已经过去，参数interval是间隔时间
bool utils::checkDuration(int interval, std::atomic<bool> &rotate_flag)
{
    static auto begin = std::chrono::steady_clock::now(); // 开始时间
    auto end = std::chrono::steady_clock::now();          // 结束时间
    if (rotate_flag)                                      // 如果旋转标志为真
    {
        begin = end;         // 更新开始时间
        rotate_flag = false; // 重置旋转标志
    }
    if (end - begin > std::chrono::milliseconds(interval)) // 如果时间间隔大于给定的间隔时间
    {
        begin = end; // 更新开始时间
        return true; // 返回true
    }
    return false; // 否则返回false
}

// 生成一个在[min, max]范围内的随机数
int utils::generateRandomNumber(int min, int max)
{
    // 使用当前时间作为种子
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);                    // 生成器
    std::uniform_int_distribution<int> dis(min, max); // 均匀分布
    return dis(gen);                                  // 返回生成的随机数
}

// 绘制当前计时时间
inline void drawTick(std::chrono::milliseconds endure)
{
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(endure).count();      // 分
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(endure).count() % 60; // 秒
    auto milliseconds = endure.count() % 1000;                                            // 毫秒

    terminal::reset();
    terminal::setCursor(20, 44);
    terminal::setColor(terminal::Color::White, true);
    terminal::setStyle(terminal::Style::Underline);
    terminal::drawTick(minutes, seconds, milliseconds);
}

// 设置一个持续时间，参数interval是持续时间
void utils::durate(int interval)
{
    static auto start = std::chrono::system_clock::now();
    auto begin = std::chrono::system_clock::now();                                      // 开始时间
    auto now = begin;                                                                   // 当前时间
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin); // 持续时间
    auto endure = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);   // 更新计时时间
    drawTick(endure);                                                                   // 打印计时时间
    while (duration.count() < interval)                                                 // 如果持续时间小于给定的间隔时间
    {
        now = std::chrono::system_clock::now();                                        // 更新当前时间
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - begin); // 更新持续时间
    }
}

// 将一个方块宽度转换为字符宽度，参数val是方块
int utils::b2c(int val)
{
    return val * 2 - 1;
}

// 获取分数，参数score是当前的分数
int utils::getScore(int score)
{
    terminal::reset();                                // 重置终端
    terminal::setCursor(19, 51);                      // 设置光标位置
    terminal::setColor(terminal::Color::White, true); // 设置颜色
    terminal::write(score);                           // 输出分数
    return score;                                     // 返回分数
}