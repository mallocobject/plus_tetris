#include "terminal.h"

// 用于保护 std::cout 的互斥锁
std::mutex cout_mtx;

// 设置控制台颜色的函数，使用256色模式
void terminal::setColor(Color color, bool isForeground)
{
    // 使用互斥锁保护 cout，防止多线程同时操作导致的问题
    std::lock_guard<std::mutex> lock(cout_mtx);
    // 根据是否设置为前景色，选择相应的 ANSI escape code
    std::cout << "\033[" << (isForeground ? 38 : 48) << ";5;" << static_cast<int>(color) << 'm';
}

// 设置控制台样式的函数
void terminal::setStyle(Style style)
{
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << "\033[" << static_cast<int>(style) << 'm';
}

// 设置光标位置的函数
void terminal::setCursor(int row, int col)
{
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << "\033[" << row << ';' << col << 'H';
}

// 隐藏光标的函数
void terminal::hideCursor()
{
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << "\033[?25l";
}

// 显示光标的函数
void terminal::showCursor()
{
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << "\033[?25h";
}

// 清屏的函数
void terminal::clearScreen()
{
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << "\033[2J";
}

// 重置控制台的函数
void terminal::reset()
{
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << "\033[0m";
}