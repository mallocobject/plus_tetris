#pragma once

#include <iostream>

namespace terminal
{
    enum class Color
    {
        Default = 9,
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

    void reset();

    template <typename T>
    void write(T &&text)
    {
        std::cout << text;
    }

    template <typename T>
    void fwrite(T &&text)
    {
        std::cout << text << std::flush;
    }
} // namespace terminal
