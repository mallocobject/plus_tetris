#pragma once

#include "define.h"

namespace tetromino
{
    // I,
    // J,
    // L,
    // O,
    // S,
    // T,
    // Z
    using Tetromino = std::array<std::array<std::pair<int, int>, 4>, 4>;
    using Tetromino_ref = std::array<std::array<std::pair<int, int>, 4>, 4> &;

    void rotate(Tetromino_ref matrix);
    void draw(tetromino::Tetromino_ref matrix, int top, int left, int index);
} // namespace tetromino