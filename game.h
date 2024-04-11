#pragma once

#include "tetromino.h"
#include <thread>
#include <unordered_map>
#include <functional>
#include <vector>
#include "piece.h"

class Piece; //< 前向声明 Piece 类

// 定义 Tetromino_ref 为一个 4x4 的 pair<int, int> 数组的引用
using Tetromino_ref = std::array<std::array<std::pair<int, int>, 4>, 4> &;

struct Game
{
public:
    ~Game();                                //< 析构函数
    Game(const Game &) = delete;            //< 删除复制构造函数
    Game &operator=(const Game &) = delete; //< 删除复制赋值运算符
    Game(Game &&) = delete;                 //< 删除移动构造函数
    Game &operator=(Game &&) = delete;      //< 删除移动赋值运算符

    using Matrix = std::vector<std::vector<int>>; //< 定义 Matrix 为一个二维 int 向量

    // 获取 Game 实例的函数
    static Game *getInstance();

    // 开始游戏
    static void start();

    // 更新游戏状态
    static void update();

    // 渲染游戏界面
    static void render(int top, int left);

    // 结束游戏
    static void end();

    // 运行子线程
    static std::thread runSubThread();

    // 设置帧率
    static void setFPS(int fps);

    // 设置持续时间
    static void setDuration(int interval);

    // 设置下落间隔
    static void setDropInterval(int interval);

    // 设置主窗口
    static void setMainWindow(int top, int left, int height, int width, const std::string &title);

    // 设置帮助窗口
    static void setHelpWindow(int top, int left, int height, int width, const std::string &title);

    // 设置帧率和分数窗口
    static void setFPSandScoreWindow(int top, int left, int height, int width, const std::string &title);

    // 设置保持窗口
    static void setHoldWindow(int top, int left, int height, int width, const std::string &title);

    // 设置下一个窗口
    static void setNextWindow(int top, int left, int height, int width, const std::string &title);

    // 旋转方块
    static void rotate();

    // 下移方块
    static void down();

    // 左移方块
    static void left();

    // 右移方块
    static void right();

    // 快速下落
    static void fastDrop();

    // 设置信号处理器
    static void setSignalHandler();

    static std::atomic<bool> running_flag;                           //< 运行标志
    static Piece piece;                                              //< 当前方块
    static Matrix *playfield;                                        //< 游戏区域
    static Matrix *frame;                                            //< 游戏框架
    static int duration;                                             //< 游戏持续时间
    static std::unordered_map<char, std::function<void()>> *key_map; //< 键盘映射

    static Game *gm; //< 游戏实例

private:
    Game() = default; //< 默认构造函数

    // 处理信号
    static void handleSignals();
};