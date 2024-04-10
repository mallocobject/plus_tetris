#include "define.h"
#include "game.h"

int main()
{
    Game *gm = Game::getInstance();             // 获取 Game 类的实例
    gm->start();                                // 开始游戏
    gm->setDropInterval(500);                   // 设置方块下落的间隔时间为 500 毫秒
    gm->setNextWindow(1, 21, 14, 5, "NEXT");    // 设置 next 窗口的位置和大小，以及窗口的标题
    gm->setScoreWindow(17, 21, 4, 5, "SCORE");  // 设置 score 窗口的位置和大小，以及窗口的标题
    gm->setMainWindow(1, 10, 20, 10, "TETRIS"); // 设置游戏窗口的位置和大小，以及窗口的标题
    gm->setHoldWindow(1, 4, 4, 5, "HOLD");      // 设置 hold 窗口的位置和大小，以及窗口的标题
    gm->setHelpWindow(7, 4, 14, 5, "HELP");     // 设置 help 窗口的位置和大小，以及窗口的标题
    std::thread th = gm->runSubThread();        // 在一个新的线程中监听键盘输入
    while (gm->running_flag)                    // 当游戏正在运行时，原子变量 running_flag防止读写冲突
    {
        gm->update();        // 更新游戏状态
        gm->render(2, 11);   // 渲染游戏画面
        gm->setDuration(10); // 设置每一帧的持续时间为 10 毫秒
    }
    th.join(); // 等待游戏的主循环线程结束
    gm->end(); // 结束游戏
    return 0;
}