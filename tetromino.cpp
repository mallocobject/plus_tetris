#include "tetromino.h"

// {center position}, {relative position}, ...
// 直角坐标系
using namespace terminal;
tetromino::Tetromino I = {{{{{'I', (int)Color::Red}, {0, -1}, {0, 1}, {0, 2}}},   // 0
                           {{{'I', (int)Color::Red}, {0, 1}, {0, -1}, {0, -2}}},  // R
                           {{{'I', (int)Color::Red}, {0, -2}, {0, -1}, {0, 1}}},  // L
                           {{{'I', (int)Color::Red}, {0, 2}, {0, 1}, {0, -1}}}}}; // 2

tetromino::Tetromino J = {{{{{'J', (int)Color::Blue}, {0, -1}, {0, 1}, {1, 1}}},   // 0
                           {{{'J', (int)Color::Blue}, {1, 0}, {-1, 0}, {-1, -1}}}, // R
                           {{{'J', (int)Color::Blue}, {0, 1}, {0, -1}, {-1, -1}}}, // L
                           {{{'J', (int)Color::Blue}, {-1, 0}, {1, 0}, {1, 1}}}}}; // 2

tetromino::Tetromino L = {{{{{'L', (int)Color::Cyan}, {0, -1}, {0, 1}, {1, -1}}},   // 0
                           {{{'L', (int)Color::Cyan}, {0, 1}, {0, -1}, {1, 1}}},    // L
                           {{{'L', (int)Color::Cyan}, {1, 0}, {-1, 0}, {-1, 1}}},   // R
                           {{{'L', (int)Color::Cyan}, {-1, 0}, {1, 0}, {1, -1}}}}}; // 2

tetromino::Tetromino O = {{{{{'O', (int)Color::Green}, {0, 1}, {1, 0}, {1, 1}}},   // 0
                           {{{'O', (int)Color::Green}, {0, 1}, {1, 0}, {1, 1}}},   // R
                           {{{'O', (int)Color::Green}, {0, 1}, {1, 0}, {1, 1}}},   // L
                           {{{'O', (int)Color::Green}, {0, 1}, {1, 0}, {1, 1}}}}}; // 2

tetromino::Tetromino S = {{{{{'S', (int)Color::Magenta}, {0, -1}, {1, 0}, {1, 1}}},     // 0
                           {{{'S', (int)Color::Magenta}, {1, 0}, {0, 1}, {-1, 1}}},     // R
                           {{{'S', (int)Color::Magenta}, {0, 1}, {-1, 0}, {-1, -1}}},   // L
                           {{{'S', (int)Color::Magenta}, {-1, 0}, {0, -1}, {1, -1}}}}}; // 2

tetromino::Tetromino T = {{{{{'T', (int)Color::Yellow}, {0, -1}, {0, 1}, {1, 0}}},    // 0
                           {{{'T', (int)Color::Yellow}, {1, 0}, {-1, 0}, {0, 1}}},    // R
                           {{{'T', (int)Color::Yellow}, {0, 1}, {0, -1}, {-1, 0}}},   // L
                           {{{'T', (int)Color::Yellow}, {-1, 0}, {1, 0}, {0, -1}}}}}; // 2

tetromino::Tetromino Z = {{{{{'Z', (int)Color::White}, {0, -1}, {1, 0}, {1, -1}}},    // 0
                           {{{'Z', (int)Color::White}, {1, 0}, {0, 1}, {-1, 1}}},     // R
                           {{{'Z', (int)Color::White}, {0, 1}, {-1, 0}, {-1, -1}}},   // L
                           {{{'Z', (int)Color::White}, {-1, 0}, {0, -1}, {1, -1}}}}}; // 2

// 顺时针旋转

// void tetromino::rotate(Tetromino_ref matrix)
// {
//     // // matrix[i][j] = matrix[j][n - i - 1]
//     // for (size_t i = 0; i < matrix.size(); i++)
//     // {
//     //     for (size_t j = 0; j < matrix[0].size(); j++)
//     //     {
//     //         if (matrix[i][j] > 0)
//     //         {
//     //             matrix[i][j] = matrix[j][matrix.size() - i - 1];
//     //         }
//     //     }
//     // }
// }

void tetromino::draw(tetromino::Tetromino_ref matrix, int top, int left, int index)
{
    terminal::resetColor();
    terminal::setColor((Color)matrix[index][0].second, false);
    terminal::setCursor(top, utils::b2c(left));
    terminal::write("  ");
    for (const auto &p : matrix[index])
    {
        // the number pair of stored the shape and color need not to be drawn
        if (p.first >= 'A')
            continue;
        terminal::setCursor(top - p.second, utils::b2c(left + p.first));
        terminal::write("  ");
    }
}
