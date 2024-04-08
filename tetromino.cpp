#include "tetromino.h"

#include "define.h"

// {center position}, {relative position}, ...
// 直角坐标系

// useless functon
// 写着玩hhhh
void tetromino::draw(tetromino::Tetromino_ref matrix, int top, int left, int index)
{
    terminal::reset();
    terminal::setColor((terminal::Color)matrix[index][0].second, false);
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
