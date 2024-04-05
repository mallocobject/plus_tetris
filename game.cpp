#include "game.h"

void Game::start()
{
    terminal::setCursor(1, 1);
    terminal::resetColor();
    system("chcp 65001"); // UTF-8
    terminal::clearScreen();
    terminal::hideCursor();
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

void Game::update(int &top)
{
    if (utils::checkDuration(500))
    {
        top++;
    }
}

void Game::render(Tetromino_ref matrix, int top, int left, int index)
{
    terminal::resetColor();
    tetromino::draw(matrix, top, left, index);
}

void Game::end()
{
    terminal::setCursor(3, 1);
    terminal::setStyle(terminal::Style::Bold);
    terminal::setColor(terminal::Color::Red);
    std::cout << "Game Over!" << std::endl;
    system("pause");
    terminal::showCursor();
    terminal::clearScreen();
    terminal::resetColor();
    terminal::setCursor(1, 1);
}

std::thread Game::runSubThread()
{
    std::unordered_map<char, std::function<void()>> key_map;
    std::thread t(handleSignals, std::ref(key_map));
    return t;
}

void Game::setFPS(int fps)
{
}

void Game::setDuration(int interval)
{
    utils::setDuration(interval);
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

void Game::rotate(int &index)
{
    index = (index + 1) % 4;
}

void Game::down(int &top)
{
}

void Game::left(int &left)
{
}

void Game::right(int &left)
{
}

void Game::handleSignals(std::unordered_map<char, std::function<void()>> &key_map)
{
    while (running_flag)
    {
        char ch = _getch();
        if (ch == 'q')
        {
            running_flag = false;
        }
        if (key_map.find(ch) != key_map.end())
        {
            key_map[ch]();
        }
    }
}

std::atomic<bool> Game::running_flag = true;