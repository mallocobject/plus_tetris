#include "terminal.h"

// '<' and '>' are used to represent the template, need be ignored
// \033[38;2;<r>;<g>;<b>m     #RGB前景色
// \033[48;2;<r>;<g>;<b>m     #RGB背景色
// void terminal::setColor(Color color, bool isForeground)
// {
//     int r = static_cast<int>(color) / 1000000;     // acquire the value about 'r'
//     int g = static_cast<int>(color) / 1000 % 1000; // acquire the value about 'g'
//     int b = static_cast<int>(color) % 1000;        // acquire the value about 'b'
//     std::cout << "\033[" << (isForeground ? 38 : 48) + ";2;" << r << ";" << g << ";" << b << "m" << std::flush;
// }

// 非常可惜，终端不支持RGB颜色，只能使用256色
void terminal::setColor(Color color, bool isForeground)
{
    std::cout << "\033[" << (isForeground ? 38 : 48) << ";5;" << static_cast<int>(color) << 'm';
}

void terminal::setStyle(Style style)
{
    std::cout << "\033[" << static_cast<int>(style) << 'm';
}

void terminal::setCursor(int row, int col)
{
    std::cout << "\033[" << row << ';' << col << 'H';
}

void terminal::hideCursor()
{
    std::cout << "\033[?25l";
}

void terminal::showCursor()
{
    std::cout << "\033[?25h";
}

void terminal::clearScreen()
{
    std::cout << "\033[2J";
}

void terminal::reset()
{
    std::cout << "\033[0m";
}
