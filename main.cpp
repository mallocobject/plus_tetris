#include "define.h"

extern tetromino::Tetromino J;

int main()
{
    Game gm;
    gm.start();
    gm.setWindow(1, 5, 20, 10, "tetris");
    int top = 2;
    while (gm.running_flag)
    {
        gm.update(top);
        gm.render(J, top, 7, 0);
        gm.setDuration(10); // 10ms
    }
    gm.end();
    return 0;
}