#pragma once

#include <array>
#include "terminal.h"

namespace tetromino
{

    using Tetromino = std::array<std::array<std::pair<int, int>, 4>, 4>;
    using Tetromino_ref = std::array<std::array<std::pair<int, int>, 4>, 4> &;
    using namespace terminal;

    // 顺时针旋转
    // 0 -> R -> 2 -> L -> 0
    static const tetromino::Tetromino I = {{{{{'I', (int)Color::Red}, {-1, 0}, {1, 0}, {2, 0}}},   // 0
                                            {{{'I', (int)Color::Red}, {0, 1}, {0, -1}, {0, -2}}},  // R
                                            {{{'I', (int)Color::Red}, {2, 0}, {-1, 0}, {1, 0}}},   // 2
                                            {{{'I', (int)Color::Red}, {0, 2}, {0, 1}, {0, -1}}}}}; // L

    static const tetromino::Tetromino J = {{{{{'J', (int)Color::Blue}, {-1, 0}, {-1, 1}, {1, 0}}},    // 0
                                            {{{'J', (int)Color::Blue}, {0, -1}, {0, 1}, {1, 1}}},     // R
                                            {{{'J', (int)Color::Blue}, {-1, 0}, {1, 0}, {1, -1}}},    // 2
                                            {{{'J', (int)Color::Blue}, {0, 1}, {0, -1}, {-1, -1}}}}}; // L

    static const tetromino::Tetromino L = {{{{{'L', (int)Color::Cyan}, {-1, 0}, {1, 0}, {1, 1}}},    // 0
                                            {{{'L', (int)Color::Cyan}, {0, 1}, {0, -1}, {1, -1}}},   // R
                                            {{{'L', (int)Color::Cyan}, {1, 0}, {-1, 0}, {-1, 1}}},   // 2
                                            {{{'L', (int)Color::Cyan}, {0, 1}, {0, -1}, {-1, 1}}}}}; // L

    static const tetromino::Tetromino O = {{{{{'O', (int)Color::Green}, {0, 1}, {1, 0}, {1, 1}}},     // 0
                                            {{{'O', (int)Color::Green}, {1, 0}, {0, -1}, {1, -1}}},   // R
                                            {{{'O', (int)Color::Green}, {-1, 0}, {0, -1}, {-1, -1}}}, // 2
                                            {{{'O', (int)Color::Green}, {0, 1}, {-1, 0}, {-1, 1}}}}}; // L

    static const tetromino::Tetromino S = {{{{{'S', (int)Color::Magenta}, {-1, 0}, {0, 1}, {1, 1}}},     // 0
                                            {{{'S', (int)Color::Magenta}, {0, 1}, {1, 0}, {1, -1}}},     // R
                                            {{{'S', (int)Color::Magenta}, {-1, -1}, {0, -1}, {1, 0}}},   // 2
                                            {{{'S', (int)Color::Magenta}, {-1, 1}, {-1, 0}, {0, -1}}}}}; // L

    static const tetromino::Tetromino T = {{{{{'T', (int)Color::Yellow}, {-1, 0}, {0, 1}, {1, 0}}},    // 0
                                            {{{'T', (int)Color::Yellow}, {0, 1}, {0, -1}, {1, 0}}},    // R
                                            {{{'T', (int)Color::Yellow}, {-1, 0}, {1, 0}, {0, -1}}},   // 2
                                            {{{'T', (int)Color::Yellow}, {-1, 0}, {0, 1}, {0, -1}}}}}; // L

    static const tetromino::Tetromino Z = {{{{{'Z', (int)Color::White}, {-1, 1}, {0, 1}, {1, 0}}},     // 0
                                            {{{'Z', (int)Color::White}, {0, -1}, {1, 0}, {1, 1}}},     // R
                                            {{{'Z', (int)Color::White}, {-1, 0}, {0, -1}, {1, -1}}},   // 2
                                            {{{'Z', (int)Color::White}, {-1, -1}, {-1, 0}, {0, 1}}}}}; // L

    // useless functon
    void draw(tetromino::Tetromino_ref matrix, int top, int left, int index);
} // namespace tetromino