#pragma once // 防止头文件被多次包含

#include "define.h" // 引入define头文件

// 定义一个名为utils的命名空间，包含一些实用函数
namespace utils
{
    // 获取当前的帧率，参数frame_count是一个引用，可能会被函数修改
    int getFPS(int &frame_count);

    // 获取当前的时间戳，返回值是一个长整型
    long long getCurrentTimestamp();

    // 检查给定的间隔时间是否已经过去，参数interval是间隔时间
    bool checkDuration(int interval, std::atomic<bool> &rotate_flag);

    // 生成一个在[min, max]范围内的随机数
    int generateRandomNumber(int min, int max);

    // 设置一个持续时间，参数interval是持续时间
    void durate(int interval);

    // 将一个方块宽度转换为字符宽度，参数val是方块
    int b2c(int val);

    // 获取分数，参数score是当前的分数
    int getScore(int score);
} // namespace utils