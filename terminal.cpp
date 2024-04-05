#include "terminal.h"

void terminal::setColor(Color color, bool isForeground)
{
    std::cout << "\033[" << (isForeground ? 30 : 40) + static_cast<int>(color) << "m";
}

void terminal::setStyle(Style style)
{
    std::cout << "\033[" << static_cast<int>(style) << "m";
}

void terminal::setCursor(int row, int col)
{
    std::cout << "\033[" << row << ";" << col << "H";
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
