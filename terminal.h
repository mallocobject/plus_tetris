#pragma once

#include <iostream>
#include <mutex>

// 用于保护 std::cout 的互斥锁
extern std::mutex cout_mtx;

namespace terminal
{
    // 控制台颜色枚举
    enum class Color
    {
        Default = 59, // 默认颜色
        White = 231,  // 白色
        Black = 0,    // 黑色
        Cyan = 48,    // 青色
        Blue = 21,    // 蓝色
        Orange = 208, // 橙色
        Yellow = 226, // 黄色
        Green = 46,   // 绿色
        Purple = 93,  // 紫色
        Red = 196     // 红色
    };

    // 控制台样式枚举
    enum class Style
    {
        Reset = 0, // 重置样式
        Bold,      // 粗体
        Dim,       // 暗淡
        Italic,    // 斜体
        Underline, // 下划线
        Blink,     // 闪烁
        Invert,    // 反转
        Hidden     // 隐藏
    };

    // 设置控制台颜色的函数
    void setColor(Color color, bool isForeground = true);

    // 设置控制台样式的函数
    void setStyle(Style style);

    // 设置光标位置的函数
    void setCursor(int row, int col);

    // 隐藏光标的函数
    void hideCursor();

    // 显示光标的函数
    void showCursor();

    // 清屏的函数
    void clearScreen();

    // 重置控制台的函数
    void reset();

    // 输出文本的函数，线程安全
    template <typename T>
    void write(T &&text)
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << text;
    }

    // 输出文本并刷新缓冲区的函数，线程安全
    template <typename T>
    void fwrite(T &&text)
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << text << std::flush;
    }
} // namespace terminal