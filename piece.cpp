#include "piece.h"
#include "define.h"

Piece::Piece(tetromino::Tetromino t, int xo, int yo, int index, Matrix *playfield)
    : t(t), xo(xo), yo(yo), index(index), playfield(playfield) {}

Piece Piece::generatePiece(Matrix *playfield)
{
    static std::unordered_map<int, tetromino::Tetromino> tetrominos = {
        {0, tetromino::I},
        {1, tetromino::J},
        {2, tetromino::L},
        {3, tetromino::O},
        {4, tetromino::S},
        {5, tetromino::T},
        {6, tetromino::Z},
    };
    int tetromino_category = utils::generateRandomNumber(0, 6);
    tetromino::Tetromino t = tetrominos[tetromino_category];
    int xo = utils::generateRandomNumber(1, 8);
    if (tetromino_category == 0 && xo == 8)     // I
        xo = utils::generateRandomNumber(1, 7); // 7
    int yo = 21;
    return Piece(t, xo, yo, 0, playfield);
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
    if (isValid(xo, yo, (index + 1) % 4))
        index = (index + 1) % 4;
}

bool Piece::isValid(int xo, int yo, int _index)
{
    for (int i = 0; i < 4; i++)
    {
        auto [dx, dy] = getTetroPosition(i, _index);
        // if the position is out of bounds
        if (xo + dx < 0 || xo + dx >= (playfield->size()) || yo + dy < 2 || yo + dy >= (*playfield)[0].size()) //
            return false;
        // if the position is occupied
        if (yo + dy < playfield[0].size() && (*playfield)[xo + dx][yo + dy] > 0)
            return false;
    }
    return true;
}

std::pair<int, int> Piece::getTetroPosition(int offset, int _index)
{
    assert(offset >= 0 && offset < 4);
    if (offset == 0)
        return {0, 0};
    return t[_index][offset];
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
    if (isValid(xo + dx, yo + dy, index))
    {
        xo += dx;
        yo += dy;
    }
}
