#include "piece.h"

Piece Piece::generatePiece()
{

    int x = 5;
    int y = 0;
    terminal::Color color = terminal::Color::Red;
    int index = 0;
    return Piece(x, y, color, index);
}

void Piece::down()
{
    move(0, 1);
}

void Piece::left()
{
    move(-1, 0);
}

void Piece::right()
{
    move(1, 0);
}

void Piece::rotate()
{
    // do nothing
}

bool Piece::isValid(int x, int y)
{
    if (x >= 0 && x < 10 && y >= 0 && y < 20)
        return true;
    return false;
}

void Piece::move(int dx, int dy)
{
    if (isValid(x + dx, y + dy))
    {
        x += dx;
        y += dy;
    }
}
