#include "piece.h"
#include "define.h"

// 构造函数，初始化方块类型、位置和索引
Piece::Piece(tetromino::Tetromino t, int xo, int yo, int index)
    : t(t), xo(xo), yo(yo), index(index) {}

// 生成一个新的方块
Piece Piece::generatePiece(Matrix *playfield)
{
    Piece::playfield = playfield;
    // 定义所有的方块类型
    static std::unordered_map<int, tetromino::Tetromino> tetrominos = {
        {0, tetromino::I},
        {1, tetromino::J},
        {2, tetromino::L},
        {3, tetromino::O},
        {4, tetromino::S},
        {5, tetromino::T},
        {6, tetromino::Z},
    };
    if (!nextTetroes)
    {
        initNextTetroes(tetrominos);
    }
    // 随机生成一个方块类型
    int tetromino_category = utils::generateRandomNumber(0, 6);
    tetromino::Tetromino t = tetrominos[tetromino_category];
    // 随机生成方块的初始位置
    int xo = utils::generateRandomNumber(1, 8);
    if (tetromino_category == 0 && xo == 8)     // I
        xo = utils::generateRandomNumber(1, 7); // 7
    tetromino::Tetromino currentTetromimo = nextTetroes->at(0).first;
    int current_xo = nextTetroes->at(0).second;
    for (int i = 0; i < 3; i++)
    {
        nextTetroes->at(i) = nextTetroes->at(i + 1);
    }
    nextTetroes->at(3) = {t, xo};
    // 如果位置不可用，清空游戏区域
    if (!isPositionFree(current_xo, 21, currentTetromimo))
    {
        for (auto &row : *playfield)
        {
            std::fill(row.begin(), row.end(), 0);
            score = 0;
        }
    }
    // 刷新hold区
    utils::draw(currentTetromimo, 4, 6);
    // 刷新next区
    int next_top = 4;
    for (const auto &p : *nextTetroes)
    {
        utils::draw(p.first, next_top, 24);
        next_top += 4;
    }
    return Piece(currentTetromimo, current_xo, 21, 0);
}

void Piece::initNextTetroes(const std::unordered_map<int, tetromino::Tetromino> &tetrominos)
{
    nextTetroes = new std::vector<std::pair<tetromino::Tetromino, int>>(4);
    int tetromino_category = 0;
    int xo = 0;
    for (int i = 0; i < 4; i++)
    {
        // 随机生成一个方块类型
        tetromino_category = utils::generateRandomNumber(0, 6);
        tetromino::Tetromino t = tetrominos.at(tetromino_category);
        // 随机生成方块的初始位置
        xo = utils::generateRandomNumber(1, 8);
        if (tetromino_category == 0 && xo == 8)     // I
            xo = utils::generateRandomNumber(1, 7); // 7
        nextTetroes->at(i) = {t, xo};
    }
}

void Piece::deleteNextTetroes()
{
    if (nextTetroes)
    {
        delete nextTetroes;
        nextTetroes = nullptr;
    }
}

// 获取方块的位置
std::pair<int, int> specialized_getTetroPosition(tetromino::Tetromino t, int offset)
{
    assert(offset >= 0 && offset < 4);
    if (offset == 0)
        return {0, 0};
    return t[0][offset];
}

// 绘制方块
void utils::draw(tetromino::Tetromino t, int top, int left)
{
    // 重置HOLD区
    terminal::reset();
    terminal::setCursor(top - 1, utils::b2c(left - 1));
    terminal::fwrite("          ");
    terminal::setCursor(top, utils::b2c(left - 1));
    terminal::fwrite("          ");

    // 绘制HLOD区
    terminal::setColor((terminal::Color)t[0][0].second, false);
    for (int i = 0; i < 4; i++)
    {
        auto [dx, dy] = specialized_getTetroPosition(t, i);
        terminal::setCursor(top - dy, utils::b2c(left + dx));
        terminal::write("  ");
    }
}

void Piece::setFlag(std::atomic<bool> *runnig_flag, std::atomic<bool> *rotate_flag)
{
    Piece::running_flag = runnig_flag;
    Piece::rotate_flag = rotate_flag;
}

// 方块下移
void Piece::down()
{
    move(0, -1, true);
}

// 方块左移
void Piece::left()
{
    move(-1, 0);
}

// 方块右移
void Piece::right()
{
    move(1, 0);
}

// 旋转方块
void Piece::rotate()
{
    if (isValid(xo, yo, (index + 1) % 4))
    {
        index = (index + 1) % 4;
        *rotate_flag = true;
        return;
    }
    else if (t != tetromino::O)
    {
        *rotate_flag = true;
        rotateTest(xo, yo);
    }
}

// 测试旋转
void Piece::rotateTest(int xo, int yo)
{
    for (const auto &p : tetro_map->at(t)[index])
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

// 检查位置是否有效
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

// 快速下落
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
// 检查 Piece 对象的位置是否有效
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
                *this = generatePiece(playfield);
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
                *this = generatePiece(playfield);
            }
            return false;
        }
    }
    return true;
}

// 清除行
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

// 获取方块的位置
std::pair<int, int> Piece::getTetroPosition(int offset, int _index)
{
    assert(offset >= 0 && offset < 4);
    if (offset == 0)
        return {0, 0};
    return t[_index][offset];
}

// 获取方块的“中心”位置
std::pair<int, int> Piece::getPosition()
{
    return {xo, yo};
}

// 获取方块的索引
int Piece::getIndex() const
{
    return index;
}

// 获取方块的类型
tetromino::Tetromino Piece::getTetromino() const
{
    return t;
}

// 获取方块的颜色
int Piece::getColor() const
{
    return t[index][0].second;
}

// 初始化 Tetromino 映射
void Piece::initTetroMap()
{
    tetro_map = new std::unordered_map<tetromino::Tetromino, std::vector<std::vector<std::pair<int, int>>>, tetromino::TetrominoHash>{
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
}

// 删除 Tetromino 映射
void Piece::deleteTetroMap()
{
    if (tetro_map)
    {
        delete tetro_map;
        tetro_map = nullptr;
    }
}

// 检查位置是否空闲
bool Piece::isPositionFree(int xo, int yo, tetromino::Tetromino t)
{
    if ((*playfield)[xo][yo] > 0)
    {
        return false;
    }
    return !std::any_of(t[0].begin() + 1, t[0].end(), [xo, yo](const auto &pos)
                        { return (*playfield)[xo + pos.first][yo] > 0; });
}

// 移动方块
void Piece::move(int dx, int dy, bool isDown)
{
    if (isValid(xo + dx, yo + dy, index, false, isDown))
    {
        xo += dx;
        yo += dy;
    }
}

Matrix *Piece::playfield = nullptr;               // 游戏区域
std::atomic<bool> *Piece::running_flag = nullptr; // 运行标志
std::atomic<bool> *Piece::rotate_flag = nullptr;  // 旋转标志
int Piece::score = 0;                             // 分数

std::unordered_map<tetromino::Tetromino, std::vector<std::vector<std::pair<int, int>>>, tetromino::TetrominoHash> *Piece::tetro_map = nullptr; // Tetromino 映射
std::vector<std::pair<tetromino::Tetromino, int>> *Piece::nextTetroes;                                                                         // 存储的方块