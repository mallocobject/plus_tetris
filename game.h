#pragma once

#include "tetromino.h"
#include <thread>
#include <unordered_map>
#include <functional>
#include <vector>
#include "piece.h"

class Piece; // forward declaration

using Tetromino_ref = std::array<std::array<std::pair<int, int>, 4>, 4> &;

struct Game
{
public:
    ~Game();
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(Game &&) = delete;

    using Matrix = std::vector<std::vector<int>>;
    static Game *getInstance();

    static void start();
    static void update();
    static void render(int top, int left);
    static void end();
    static std::thread runSubThread();
    static void setFPS(int fps);
    static void setDuration(int interval);
    static void setDropInterval(int interval);
    // static void setWindow(int top, int left, int height, int width, const std::string &title);
    static void setMainWindow(int top, int left, int height, int width, const std::string &title);
    static void setHelpWindow(int top, int left, int height, int width, const std::string &title);
    static void setScoreWindow(int top, int left, int height, int width, const std::string &title);
    static void setHoldWindow(int top, int left, int height, int width, const std::string &title);
    static void setNextWindow(int top, int left, int height, int width, const std::string &title);
    static void rotate();
    static void down();
    static void left();
    static void right();
    static void fastDrop();
    static void setSignalHandler();

    static std::atomic<bool> running_flag;
    static Piece piece;
    static Matrix *playfield;
    static Matrix *frame;
    static int duration;
    static std::unordered_map<char, std::function<void()>> *key_map;

    static Game *gm;

private:
    Game() = default;

    static void handleSignals();
};