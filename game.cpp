#include "game.h"
#include "define.h"

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

void Game::start()
{
    terminal::setCursor(1, 1);
    terminal::reset();
    system("chcp 65001"); // UTF-8
    terminal::clearScreen();
    terminal::hideCursor();
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    // frame = playfield;
    setSignalHandler();
}

void Game::update()
{
    // drop naturally
    if (utils::checkDuration(duration))
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

void Game::render(int top, int left)
{
    static int count = 0;
    count++;
    utils::getFPS(count);
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
                terminal::write("\u25fb");
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

void Game::end()
{
    terminal::reset();
    terminal::setCursor(1, 1);
    terminal::setColor(terminal::Color::Red);
    terminal::fwrite("Game Over! Press any key to exit...");
    system("pause > nul");
    terminal::clearScreen();
    terminal::setCursor(1, 1);
    terminal::showCursor();
    terminal::reset();
    flush(std::cout);
}

std::thread Game::runSubThread()
{
    return std::thread(&Game::handleSignals);
}

void Game::setFPS(int fps)
{
}

void Game::setDuration(int interval)
{
    utils::setDuration(interval);
}

void Game::setDropInterval(int interval)
{
    duration = interval;
}

void Game::setWindow(int top, int left, int height, int width, const std::string &title)
{

    terminal::setColor(terminal::Color::White);
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

    terminal::setCursor(top, utils::b2c(left) + 2 + (width * 2 - title.size()) / 2);
    terminal::setColor(terminal::Color::Green, true);
    terminal::fwrite(title);
}

void Game::rotate()
{
    piece.rotate();
}

void Game::down()
{
    piece.down();
}

void Game::left()
{
    piece.left();
}

void Game::right()
{
    piece.right();
}

void Game::fastDrop()
{
    piece.fastDrop();
}

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
Matrix *Game::playfield = new std::vector<std::vector<int>>(10, std::vector<int>(22, 0));
Matrix *Game::frame = new std::vector<std::vector<int>>(10, std::vector<int>(22, 0));
Piece Game::piece = Piece::generatePiece(playfield, &running_flag);
int Game::duration = 500; // 500ms
std::unordered_map<char, std::function<void()>> *Game::key_map = nullptr;