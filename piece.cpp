#include "piece.h"
#include "define.h"

Piece::Piece(tetromino::Tetromino t, int xo, int yo, int index, Matrix *playfield)
    : t(t), xo(xo), yo(yo), index(index), playfield(playfield) {}

Piece Piece::generatePiece(Matrix *playfield)
{
    tetromino::Tetromino t = tetromino::J;
    int index = 1;
    int xo = 5;
    int yo = 22;
    return Piece(t, xo, yo, index, playfield);
}

void Piece::down()
{
    move(0, -1);
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
    index = (index + 1) % 4;
}

bool Piece::isValid(int xo, int yo)
{
    for (int i = 0; i < 4; i++)
    {
        auto [dx, dy] = getTetroPosition(i);
        // if the position is out of bounds
        if (xo + dx < 0 || xo + dx >= (playfield->size()) || yo + dy < 2 || yo + dy >= (*playfield)[0].size())
            return false;
        // if the position is occupied
        if ((*playfield)[xo + dx][yo + dy] > 0)
            return false;
    }
    return true;
}

std::pair<int, int> Piece::getTetroPosition(int p)
{
    assert(p >= 0 && p < 4);
    if (p == 0)
        return {0, 0};
    return t[index][p];
}

std::pair<int, int> Piece::getPosition()
{
    return {xo, yo};
}

int Piece::getIndex() const
{
    return index;
}

tetromino::Tetromino Piece::getTetromino() const
{
    return t;
}

int Piece::getColor() const
{
    return t[index][0].second;
}

void Piece::move(int dx, int dy)
{
    if (isValid(xo + dx, yo + dy))
    {
        xo += dx;
        yo += dy;
    }
}
