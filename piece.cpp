#include "piece.h"
#include "define.h"

Piece::Piece(tetromino::Tetromino t, int xo, int yo, int index)
    : t(t), xo(xo), yo(yo), index(index) {}

Piece Piece::generatePiece(Matrix *playfield, std::atomic<bool> *running_flag)
{
    Piece::playfield = playfield;
    Piece::running_flag = running_flag;
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
    if (!isPositionFree(xo, yo, t))
    {
        for (auto &row : *playfield)
        {
            // *playfield = Matrix(10, std::vector<int>(22, 0));
            // the above code is the mother-fucking code
            // The second operation will not work
            terminal::reset();
            terminal::setCursor(1, 40);
            int color_type = utils::generateRandomNumber(1, 7);
            terminal::setColor((terminal::Color)color_type);
            terminal::fwrite("You are failed");

            std::fill(row.begin(), row.end(), 0);
            score = 0;
        }
    }
    return Piece(t, xo, yo, 0);
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
void Piece::fastDrop()
{
    // 这里的false标志位很重要，如果传递true则要等下一个循环，转移键盘响应piece
    while (isValid(xo, yo - 1, index, false))
    {
        this->yo--;
    }
}
// isShadow is a flag to indicate whether the piece is a shadow piece
// 函数的默认参数值应该只在函数声明中给出，不应在函数定义中再次给出
bool Piece::isValid(int xo, int yo, int _index, bool isShadow)
{
    // int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        auto [dx, dy] = getTetroPosition(i, _index);
        int color = getColor();

        // if the position is out of bounds
        if (xo + dx < 0 || xo + dx >= (playfield->size()))
            return false;
        else if (yo + dy < 2)
        {
            if (!isShadow)
            {
                yo++; // recover the position
                for (int i = 0; i < 4; i++)
                {
                    auto [dx, dy] = this->getTetroPosition(i, _index);
                    (*playfield)[xo + dx][yo + dy] = color; // color as value
                }
                *this = generatePiece(playfield, running_flag);
            }
            return false;
        }
        // if the position is occupied
        else if (yo + dy < (*playfield)[0].size() && (*playfield)[xo + dx][yo + dy] > 0)
        {
            if (!isShadow)
            {
                yo++; // recover the position
                for (int i = 0; i < 4; i++)
                {
                    auto [dx, dy] = this->getTetroPosition(i, _index);
                    (*playfield)[xo + dx][yo + dy] = color; // color as value
                }

                // clear rows
                clearRows();

                *this = generatePiece(playfield, running_flag);
            }
            return false;
        }
    }
    return true;
}

void Piece::clearRows()
{
    for (int y = 2; y < playfield->front().size(); y++)
    {
        // Check if the row is full
        if (std::all_of(playfield->begin(), playfield->end(), [y](const auto &row)
                        { return row[y] > 0; }))
        {
            score++; // Increase the score: clear 1 line = 1 point
            // Clear the row...
            for (int y1 = y; y1 < playfield->front().size(); y1++)
            {
                for (int x = 0; x < playfield->size(); x++)
                {
                    if (y1 == playfield->front().size() - 1)
                    {
                        (*playfield)[x][y1] = 0;
                    }
                    else
                    {
                        (*playfield)[x][y1] = (*playfield)[x][y1 + 1];
                    }
                }
            }
        }
    }
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

bool Piece::isPositionFree(int xo, int yo, tetromino::Tetromino t)
{
    if ((*playfield)[xo][yo] > 0)
    {
        return false;
    }
    return !std::any_of(t[0].begin() + 1, t[0].end(), [xo, yo](const auto &pos)
                        { return (*playfield)[xo + pos.first][yo] > 0; });
}

void Piece::move(int dx, int dy)
{
    if (isValid(xo + dx, yo + dy, index))
    {
        xo += dx;
        yo += dy;
    }
}

Matrix *Piece::playfield = nullptr;
std::atomic<bool> *Piece::running_flag = nullptr;
int Piece::score = 0;
