#include "game.h"
#include "define.h"

// 析构函数，释放动态分配的内存
Game::~Game()
{
    if (!playfield)
    {
        delete playfield;
        playfield = nullptr;
    }
    if (!frame)
    {
        delete frame;
        frame = nullptr;
    }
    if (!key_map)
    {
        delete key_map;
        key_map = nullptr;
    }
    // std::cout << "Game Over!" << std::endl;
}

// 获取游戏实例，如果不存在则创建
Game *Game::getInstance()
{
    if (gm == nullptr)
    {
        gm = new Game();
    }
    return gm;
}

// 开始游戏，初始化环境和游戏数据
void Game::start()
{
    Piece::setFlag(&running_flag, &rotate_flag);
    terminal::setCursor(1, 1);
    terminal::reset();
    system("chcp 65001"); // UTF-8
    terminal::clearScreen();
    terminal::hideCursor();
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // frame = playfield;
    setSignalHandler();                      // set signal handler
    Piece::initTetroMap();                   // init tetro_map
    piece = Piece::generatePiece(playfield); // generate a new piece
}

// 更新游戏状态，包括自然下落和阴影块的处理
void Game::update()
{
    // drop naturally
    if (utils::checkDuration(duration, rotate_flag))
        piece.down();

    (*frame) = (*playfield);
    auto [xo, yo] = piece.getPosition();
    int index = piece.getIndex();
    tetromino::Tetromino t = piece.getTetromino();
    // int color = piece.getColor();
    // normal block
    for (int i = 0; i < 4; i++)
    {
        auto [dx, dy] = piece.getTetroPosition(i, index);
        (*frame)[xo + dx][yo + dy] = t[index][0].second; // color as value
    }

    // shadow block
    while (piece.isValid(xo, yo - 1, index, true))
    {
        yo--;
    }
    for (int i = 0; i < 4; i++)
    {
        auto [dx, dy] = piece.getTetroPosition(i, index);
        if ((*frame)[xo + dx][yo + dy] == 0)
            (*frame)[xo + dx][yo + dy] = -t[index][0].second; // color as value
    }
}

// 渲染游戏画面
void Game::render(int top, int left)
{
    static int count = 0;
    count++;
    utils::getFPS(count);
    utils::getScore(piece.score);
    int n = (*frame)[0].size();
    for (int i = 0; i < (*frame).size(); i++)
    {
        for (int j = 2; j < n; j++)
        {
            terminal::setCursor(top + n - j - 1, utils::b2c(left + i));
            // 空白区不写入颜色
            // 前景色和背景色可重叠
            terminal::reset(); // reset color
            // background
            if ((*frame)[i][j] == 0)
            {
                // terminal::setColor(terminal::Color::Green, true);
                terminal::write("\u30fb");
            }
            // shadow block
            else if ((*frame)[i][j] < 0)
            {
                terminal::setColor((terminal::Color)(-(*frame)[i][j]), true);
                terminal::write("\u25a2 ");
            }
            // normal block
            else
            {
                terminal::setColor((terminal::Color)(*frame)[i][j], false);
                terminal::write("  ");
            }
        }
    }
}

// 结束游戏，释放资源
void Game::end()
{
    terminal::reset();
    terminal::setCursor(8, 11);
    terminal::setStyle(terminal::Style::Bold);
    terminal::setColor(terminal::Color::Red);
    terminal::fwrite("Game Over! Press any key to exit...");
    system("pause > nul");
    terminal::clearScreen();
    terminal::setCursor(1, 1);
    terminal::showCursor();
    terminal::reset();
    flush(std::cout);
    if (gm)
    {
        delete gm; // delete instance
        gm = nullptr;
    }
    Piece::deleteTetroMap();    // delete tetro_map
    Piece::deleteNextTetroes(); // delete store_tetroes
}

// 运行子线程处理信号
std::thread Game::runSubThread()
{
    return std::thread(&Game::handleSignals);
}

// 设置游戏帧率
void Game::setFPS(int fps)
{
}

// 延迟
void Game::durate(int interval)
{
    utils::durate(interval);
}

// 设置方块自然下落的间隔
void Game::setDropInterval(int interval)
{
    duration = interval;
}

// 设置窗口样式和标题
void setWindow(int top, int left, int height, int width, const std::string &title, bool isCenter = false)
{
    terminal::reset();
    terminal::setColor(terminal::Color::White, true);
    terminal::setCursor(top, utils::b2c(left));
    terminal::write(" ┌");
    for (int i = 0; i < width; i++)
    {
        terminal::write("──");
    }
    terminal::write("┐");

    for (int i = 1; i <= height; i++)
    {
        terminal::setCursor(top + i, utils::b2c(left) + 1);
        terminal::write("│");
        terminal::setCursor(top + i, utils::b2c(left + width) + 2);
        terminal::write("│");
    }

    terminal::setCursor(top + height + 1, utils::b2c(left));
    terminal::write(" └");
    for (int i = 0; i < width; i++)
    {
        terminal::write("──");
    }
    terminal::write("┘");

    if (isCenter)
    {
        terminal::setCursor(top, utils::b2c(left) + 2 + (width * 2 - title.size()) / 2);
    }
    else
    {
        terminal::setCursor(top, utils::b2c(left) + 1);
    }
    terminal::setColor(terminal::Color::Green, true);
    terminal::setStyle(terminal::Style::Italic);
    terminal::write(title);
}

// 设置主窗口
void Game::setMainWindow(int top, int left, int height, int width, const std::string &title)
{
    setWindow(top, left, height, width, title, true);
}

// 设置帮助窗口
void Game::setHelpWindow(int top, int left, int height, int width, const std::string &title)
{
    setWindow(top, left, height, width, title);
    terminal::reset();
    terminal::setColor(terminal::Color::White, true);
    terminal::setCursor(9, 10);
    terminal::write("w => \u21bb");
    terminal::setCursor(11, 10);
    terminal::write("s => \u2193");
    terminal::setCursor(13, 10);
    terminal::write("a => \u2190");
    terminal::setCursor(15, 10);
    terminal::write("d => \u2192");
    terminal::setCursor(17, 10);
    terminal::write("\u2420 => \u21af");
    terminal::setCursor(19, 10);
    terminal::write("q => \u292c");
}

// 设置 FPS 和分数窗口
void Game::setStatus(int top, int left, int height, int width, const std::string &title)
{
    setWindow(top, left, height, width, title);
    terminal::setColor(terminal::Color::White, true);
    terminal::setCursor(18, 44);
    terminal::write("FPS:");
    terminal::setCursor(19, 44);
    terminal::write("SCORE:");
}

// 设置 Hold 窗口
void Game::setHoldWindow(int top, int left, int height, int width, const std::string &title)
{
    setWindow(top, left, height, width, title);
    utils::draw(piece.getTetromino(), 4, 6);
}

// 设置 Next 窗口
void Game::setNextWindow(int top, int left, int height, int width, const std::string &title)
{
    setWindow(top, left, height, width, title);
}

// 旋转方块
void Game::rotate()
{
    piece.rotate();
}

// 方块向下移动
void Game::down()
{
    piece.down();
}

// 方块向左移动
void Game::left()
{
    piece.left();
}

// 方块向右移动
void Game::right()
{
    piece.right();
}

// 方块快速下落
void Game::fastDrop()
{
    piece.fastDrop();
}

// 设置信号处理函数，处理用户输入
void Game::setSignalHandler()
{
    key_map = new std::unordered_map<char, std::function<void()>>();
    (*key_map)['w'] = rotate;
    (*key_map)['s'] = down;
    (*key_map)['a'] = left;
    (*key_map)['d'] = right;
    (*key_map)[' '] = fastDrop;
    (*key_map)['q'] = []()
    { running_flag = false; };
}

// 处理用户输入的信号
void Game::handleSignals()
{
    while (running_flag)
    {
        if (_kbhit)
        {
            char ch = _getch();
            if (key_map->find(ch) != key_map->end())
            {
                key_map->at(ch)();
            }
        }
    }
}

std::atomic<bool> Game::running_flag = true;
std::atomic<bool> Game::rotate_flag = false;
Matrix *Game::playfield = new std::vector<std::vector<int>>(10, std::vector<int>(22, 0));
Matrix *Game::frame = new std::vector<std::vector<int>>(10, std::vector<int>(22, 0));
Piece Game::piece = Piece(tetromino::I, 5, 0, 0);
int Game::duration = 500; // 500ms
std::unordered_map<char, std::function<void()>> *Game::key_map = nullptr;

Game *Game::gm = nullptr;