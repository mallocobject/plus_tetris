#pragma once

#include "tetromino.h"
#include "terminal.h"
#include <vector>
#include <atomic>
#include <unordered_map>

class Piece
{
public:
    using Matrix = std::vector<std::vector<int>>; // 定义 Matrix 为一个二维 int 向量

    Piece() = delete;                                         // 删除默认构造函数
    Piece(tetromino::Tetromino t, int xo, int yo, int index); // 构造函数
    Piece(const Piece &) = default;                           // 默认复制构造函数
    Piece(Piece &&) = default;                                // 默认移动构造函数
    Piece &operator=(const Piece &) = default;                // 默认复制赋值运算符
    Piece &operator=(Piece &&) = default;                     // 默认移动赋值运算符
    ~Piece() = default;                                       // 默认析构函数

    // 生成一个新的方块
    static Piece generatePiece(Matrix *playfield);
    static void setFlag(std::atomic<bool> *runnig_flag, std::atomic<bool> *rotate_flag);

    void down();     // 下移方块
    void left();     // 左移方块
    void right();    // 右移方块
    void rotate();   // 旋转方块
    void fastDrop(); // 快速下落

    // 检查方块是否有效
    bool isValid(int xo, int yo, int _index, bool isShadow = false, bool isDown = false);

    // 获取方块位置
    std::pair<int, int> getTetroPosition(int offset, int _index);

    // 获取位置
    std::pair<int, int> getPosition();

    // 获取索引
    int getIndex() const;

    // 获取 Tetromino
    tetromino::Tetromino getTetromino() const;

    // 获取颜色
    int getColor() const;

    // 初始化 Tetromino 映射
    static void initTetroMap();

    // 删除 Tetromino 映射
    static void deleteTetroMap();

    static Matrix *playfield; // 游戏区域
    static int score;         // 分数

private:
    void clearRows();                                                   // 清除行
    static bool isPositionFree(int xo, int yo, tetromino::Tetromino t); // 检查位置是否空闲
    void move(int dx, int dy, bool isDown = false);                     // 移动方块
    void rotateTest(int xo, int yo);                                    // 旋转测试
    bool SpecializedIsValid(int xo, int yo, int _index);                // 特殊有效性检查
    tetromino::Tetromino t;                                             // Tetromino
    int xo, yo;                                                         // 直角坐标系
    int index;                                                          // 索引
    static std::atomic<bool> *running_flag;
    static std::atomic<bool> *rotate_flag;                                                                                               // 运行标志
    static std::unordered_map<tetromino::Tetromino, std::vector<std::vector<std::pair<int, int>>>, tetromino::TetrominoHash> *tetro_map; // Tetromino 映射
};

namespace utils
{
    void draw(tetromino::Tetromino t, int top, int left); // 绘制 Tetromino
} // namespace utils