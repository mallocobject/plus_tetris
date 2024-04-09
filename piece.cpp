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
            terminal::fwrite("You are failed!");

            std::fill(row.begin(), row.end(), 0);
            score = 0;
        }
    }
    return Piece(t, xo, yo, 0);
}

void Piece::down()
{
    move(0, -1, true);
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
    {
        index = (index + 1) % 4;
        return;
    }
    else if (t != tetromino::O)
    {
        rotateTest(xo, yo);
    }
}

void Piece::rotateTest(int xo, int yo)
{
    for (const auto &p : tetro_map[t][index])
    {
        auto [dx, dy] = p;
        if (SpecializedIsValid(xo + dx, yo + dy, (index + 1) % 4))
        {
            this->xo += dx;
            this->yo += dy;
            index = (index + 1) % 4;
            return;
        }
    }
}

bool Piece::SpecializedIsValid(int xo, int yo, int _index)
{
    for (int i = 0; i < 4; i++)
    {
        auto [dx, dy] = getTetroPosition(i, _index);
        int color = getColor();

        // if the position is out of the boundary
        if (xo + dx < 0 || xo + dx >= (playfield->size()))
        {
            return false;
        }
        else if (yo + dy < 2)
        {
            return false;
        }
        else if (yo + dy < (*playfield)[0].size() && (*playfield)[xo + dx][yo + dy] > 0)
        {
            return false;
        }
    }
    return true;
}

void Piece::fastDrop()
{
    // 这里的false标志位很重要，如果传递true则要等下一个循环，转移键盘响应piece
    while (isValid(xo, yo - 1, index, false, true))
    {
        this->yo--;
    }
}
// isShadow is a flag to indicate whether the piece is a shadow piece
// 函数的默认参数值应该只在函数声明中给出，不应在函数定义中再次给出
// 这个函数只有我和上帝看懂，或许在一周后，怕是只有上帝能看懂了
bool Piece::isValid(int xo, int yo, int _index, bool isShadow, bool isDown)
{
    // int cnt = 0;
    for (int i = 0; i < 4; i++)
    {
        auto [dx, dy] = getTetroPosition(i, _index);
        int color = getColor();

        // if the position is out of the boundary
        if (xo + dx < 0 || xo + dx >= (playfield->size()))
            return false;
        else if (yo + dy < 2)
        {
            // 至于这里为什么不能使用isShadow，我也不知道
            // 反正用了就会出问题
            // that's all
            if (!isShadow)
            {
                yo++; // recover the position
                for (int i = 0; i < 4; i++)
                {
                    auto [dx, dy] = this->getTetroPosition(i, _index);
                    (*playfield)[xo + dx][yo + dy] = color; // color as value
                }

                // clear the rows
                // only when the piece is freezed, we can clear the rows
                clearRows();
                *this = generatePiece(playfield, running_flag);
            }
            return false;
        }
        // if the below position is occupied
        else if (yo + dy < (*playfield)[0].size() && (*playfield)[xo + dx][yo + dy] > 0)
        {
            // if the piece is not a shadow piece and is moving down
            // isDown is a flag to indicate whether the piece is moving down
            if (!isShadow && isDown)
            {
                yo++; // recover the position
                for (int i = 0; i < 4; i++)
                {
                    auto [dx, dy] = this->getTetroPosition(i, _index);
                    (*playfield)[xo + dx][yo + dy] = color; // color as value
                }

                // clear the rows
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
    for (int y = playfield->front().size() - 1; y >= 2; y--)
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

void Piece::move(int dx, int dy, bool isDown)
{
    if (isValid(xo + dx, yo + dy, index, false, isDown))
    {
        xo += dx;
        yo += dy;
    }
}

Matrix *Piece::playfield = nullptr;
std::atomic<bool> *Piece::running_flag = nullptr;
int Piece::score = 0;

std::unordered_map<tetromino::Tetromino, std::vector<std::vector<std::pair<int, int>>>, tetromino::TetrominoHash> Piece::tetro_map = {
    {tetromino::I, {{{-2, 0}, {1, 0}, {-2, -1}, {1, 2}},     // 0 - R
                    {{-1, 0}, {2, 0}, {-1, 2}, {2, -1}},     // R - 2
                    {{2, 0}, {-1, 0}, {2, 1}, {-1, -2}},     // 2 - L
                    {{1, 0}, {-2, 0}, {1, -2}, {-2, 1}}}},   // L - 0
    {tetromino::J, {{{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},   // 0 - R
                    {{1, 0}, {1, -1}, {0, 2}, {1, 2}},       // R - 2
                    {{1, 0}, {1, 1}, {0, -2}, {1, -2}},      // 2 - L
                    {{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}}},  // L - 0
    {tetromino::L, {{{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},   // 0 - R
                    {{1, 0}, {1, -1}, {0, 2}, {1, 2}},       // R - 2
                    {{1, 0}, {1, 1}, {0, -2}, {1, -2}},      // 2 - L
                    {{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}}},  // L - 0
    {tetromino::S, {{{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},   // 0 - R
                    {{1, 0}, {1, -1}, {0, 2}, {1, 2}},       // R - 2
                    {{1, 0}, {1, 1}, {0, -2}, {1, -2}},      // 2 - L
                    {{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}}},  // L - 0
    {tetromino::T, {{{-1, 0}, {-1, 1}, {0, 0}, {-1, -2}},    // 0 - R
                    {{1, 0}, {1, -1}, {0, 2}, {1, 2}},       // R - 2
                    {{1, 0}, {0, 0}, {0, -2}, {1, -2}},      // 2 - L
                    {{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}}},  // L - 0
    {tetromino::Z, {{{-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},   // 0 - R
                    {{1, 0}, {1, -1}, {0, 2}, {1, 2}},       // R - 2
                    {{1, 0}, {1, 1}, {0, -2}, {1, -2}},      // 2 - L
                    {{-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}}}}; // L - 0
