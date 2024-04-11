#include "tetromino.h" // 引入tetromino头文件
#include "define.h"    // 引入define头文件

// {center position}, {relative position}, ...
// 直角坐标系

// useless function
// 写着玩的，没用
// void tetromino::draw(tetromino::Tetromino_ref matrix, int top, int left, int index)
// {
//     terminal::reset();  // 重置终端
//     terminal::setColor((terminal::Color)matrix[index][0].second, false);  // 设置颜色
//     terminal::setCursor(top, utils::b2c(left));  // 设置光标位置
//     terminal::write("  ");  // 写入空格
//     for (const auto &p : matrix[index])  // 遍历矩阵的每个元素
//     {
//         // 如果元素的first值大于等于'A'，则跳过，不进行绘制
//         if (p.first >= 'A')
//             continue;
//         terminal::setCursor(top - p.second, utils::b2c(left + p.first));  // 设置光标位置
//         terminal::write("  ");  // 写入空格
//     }
// }

// 定义TetrominoHash结构体的()运算符重载函数
// 该函数接受一个Tetromino类型的常量引用作为参数，返回其哈希值
std::size_t tetromino::TetrominoHash::operator()(Tetromino const &t) const noexcept
{
    std::size_t seed = 0;     // 初始化种子值为0
    for (const auto &row : t) // 遍历Tetromino的每一行
    {
        for (const auto &element : row) // 遍历行的每一个元素
        {
            // 使用std::hash<int>对元素的first值进行哈希，然后与种子值进行异或操作
            seed ^= std::hash<int>{}(element.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            // 使用std::hash<int>对元素的second值进行哈希，然后与种子值进行异或操作
            seed ^= std::hash<int>{}(element.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
    }
    return seed; // 返回最终的哈希值
}