#include "define.h"

int main()
{
    Game gm;
    gm.start();
    gm.setWindow(2, 5, 20, 10, "plus tetris");
    while (true)
    {
        gm.update();
        gm.render();
        gm.setDuration(10);
    }
    gm.end();
    return 0;
}