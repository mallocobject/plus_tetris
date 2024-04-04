#pragma once

#include "define.h"

namespace terminal
{
    enum class Color
    {
        Null = -1,
        Black = 0,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        White
    };

    enum class Style
    {
        Reset = 0,
        Bold,
        Dim,
        Italic,
        Underline,
        Blink,
        Invert,
        Hidden
    };

    void setColor(Color color, bool isForeground = true);

    void setStyle(Style style);

    void setCursor(int row, int col);

    void hideCursor();

    void showCursor();

    void clearScreen();

    void resetColor();

    template <typename T>
    void write(T &&text)
    {
        std::cout << text << std::flush;
    }
} // namespace terminal
