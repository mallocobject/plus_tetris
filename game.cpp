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

void Game::update()
{
}

void Game::render()
{
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
    return std::thread();
}

void Game::setFPS(int fps)
{
}

void Game::setDuration(int interval)
{
}

inline int block2col(int val)
{
    return val * 2 - 1;
}

void Game::setWindow(int row, int col, int height, int width, const std::string &title)
{
    terminal::setColor(terminal::Color::White);
    terminal::setCursor(row, block2col(col));
    terminal::write(" ┌");
    for (int i = 0; i < width; i++)
    {
        terminal::write("──");
    }
    terminal::write("┐");

    for (int i = 1; i <= height; i++)
    {
        terminal::setCursor(row + i, block2col(col) + 1);
        terminal::write("│");
        terminal::setCursor(row + i, block2col(col + width) + 2);
        terminal::write("│");
    }

    terminal::setCursor(row + height + 1, block2col(col));
    terminal::write(" └");
    for (int i = 0; i < width; i++)
    {
        terminal::write("──");
    }
    terminal::write("┘");

    terminal::setCursor(row - 1, block2col(col) + 3 + (block2col(width) - title.size()) / 2);
    terminal::setColor(terminal::Color::Green, true);
    terminal::write(title);
}
