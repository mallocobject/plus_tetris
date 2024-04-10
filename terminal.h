#pragma once

#include <iostream>
#include <mutex>

extern std::mutex cout_mtx;

namespace terminal
{
    enum class Color
    {
        Default = 59,
        White = 231,
        Black = 0,
        Cyan = 48,
        Blue = 21,
        Orange = 208,
        Yellow = 226,
        Green = 46,
        Purple = 93,
        Red = 196
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
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << text;
    }

    template <typename T>
    void fwrite(T &&text)
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << text << std::flush;
    }
} // namespace terminal
