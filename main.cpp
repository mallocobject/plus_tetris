#include "define.h"
#include "game.h"

int main()
{
    Game gm;
    gm.start();
    gm.setDropInterval(50);
    gm.setWindow(1, 5, 20, 10, "tetris");
    std::thread th = gm.runSubThread();
    while (gm.running_flag)
    {
        gm.update();
        gm.render(2, 6);
        gm.setDuration(10); // 10ms
    }
    th.join();
    gm.end();
    return 0;
}