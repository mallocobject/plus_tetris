#pragma once

#include <array>
#include "terminal.h"

namespace tetromino
{

    using Tetromino = std::array<std::array<std::pair<int, int>, 4>, 4>;
    using Tetromino_ref = std::array<std::array<std::pair<int, int>, 4>, 4> &;
    using namespace terminal;

    // 顺时针旋转
    // 定义各种形状的俄罗斯方块，每种形状有4种旋转状态，每种状态由4个坐标点表示
    // 同时把颜色和种类信息存储在中心位置(0, 0)处
    // 0 -> R -> 2 -> L -> 0
    static const tetromino::Tetromino I = {{{{{'I', (int)Color::Cyan}, {-1, 0}, {1, 0}, {2, 0}}},   // 0
                                            {{{'I', (int)Color::Cyan}, {0, 1}, {0, -1}, {0, -2}}},  // R
                                            {{{'I', (int)Color::Cyan}, {-2, 0}, {-1, 0}, {1, 0}}},  // 2
                                            {{{'I', (int)Color::Cyan}, {0, 2}, {0, 1}, {0, -1}}}}}; // L

    static const tetromino::Tetromino J = {{{{{'J', (int)Color::Blue}, {-1, 0}, {-1, 1}, {1, 0}}},    // 0
                                            {{{'J', (int)Color::Blue}, {0, -1}, {0, 1}, {1, 1}}},     // R
                                            {{{'J', (int)Color::Blue}, {-1, 0}, {1, 0}, {1, -1}}},    // 2
                                            {{{'J', (int)Color::Blue}, {0, 1}, {0, -1}, {-1, -1}}}}}; // L

    static const tetromino::Tetromino L = {{{{{'L', (int)Color::Orange}, {-1, 0}, {1, 0}, {1, 1}}},    // 0
                                            {{{'L', (int)Color::Orange}, {0, 1}, {0, -1}, {1, -1}}},   // R
                                            {{{'L', (int)Color::Orange}, {1, 0}, {-1, 0}, {-1, -1}}},  // 2
                                            {{{'L', (int)Color::Orange}, {0, 1}, {0, -1}, {-1, 1}}}}}; // L

    static const tetromino::Tetromino O = {{{{{'O', (int)Color::Yellow}, {0, 1}, {1, 0}, {1, 1}}},     // 0
                                            {{{'O', (int)Color::Yellow}, {1, 0}, {0, -1}, {1, -1}}},   // R
                                            {{{'O', (int)Color::Yellow}, {-1, 0}, {0, -1}, {-1, -1}}}, // 2
                                            {{{'O', (int)Color::Yellow}, {0, 1}, {-1, 0}, {-1, 1}}}}}; // L

    static const tetromino::Tetromino S = {{{{{'S', (int)Color::Green}, {-1, 0}, {0, 1}, {1, 1}}},     // 0
                                            {{{'S', (int)Color::Green}, {0, 1}, {1, 0}, {1, -1}}},     // R
                                            {{{'S', (int)Color::Green}, {-1, -1}, {0, -1}, {1, 0}}},   // 2
                                            {{{'S', (int)Color::Green}, {-1, 1}, {-1, 0}, {0, -1}}}}}; // L

    static const tetromino::Tetromino T = {{{{{'T', (int)Color::Purple}, {-1, 0}, {0, 1}, {1, 0}}},    // 0
                                            {{{'T', (int)Color::Purple}, {0, 1}, {0, -1}, {1, 0}}},    // R
                                            {{{'T', (int)Color::Purple}, {-1, 0}, {1, 0}, {0, -1}}},   // 2
                                            {{{'T', (int)Color::Purple}, {-1, 0}, {0, 1}, {0, -1}}}}}; // L

    static const tetromino::Tetromino Z = {{{{{'Z', (int)Color::Red}, {-1, 1}, {0, 1}, {1, 0}}},     // 0
                                            {{{'Z', (int)Color::Red}, {0, -1}, {1, 0}, {1, 1}}},     // R
                                            {{{'Z', (int)Color::Red}, {-1, 0}, {0, -1}, {1, -1}}},   // 2
                                            {{{'Z', (int)Color::Red}, {-1, -1}, {-1, 0}, {0, 1}}}}}; // L

    // useless functon
    // void draw(tetromino::Tetromino_ref matrix, int top, int left, int index);

    struct TetrominoHash
    {
        // 该函数接受一个Tetromino类型的常量引用作为参数，返回其哈希值
        std::size_t operator()(Tetromino const &t) const noexcept;
    };

} // namespace tetromino