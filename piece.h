#pragma once

#include "tetromino.h"
#include "terminal.h"
#include <vector>
#include <atomic>

class Piece
{
public:
    using Matrix = std::vector<std::vector<int>>;

    Piece() = delete;
    Piece(tetromino::Tetromino t, int xo, int yo, int index);
    Piece(const Piece &) = default;
    Piece(Piece &&) = default;
    Piece &operator=(const Piece &) = default;
    Piece &operator=(Piece &&) = default;
    ~Piece() = default;
    static Piece generatePiece(Matrix *playfield, std::atomic<bool> *running_flag);
    void down();
    void left();
    void right();
    void rotate();
    void fastDrop();
    bool isValid(int xo, int yo, int _index, bool isShadow = false);
    std::pair<int, int> getTetroPosition(int offset, int _index);
    std::pair<int, int> getPosition();
    int getIndex() const;
    tetromino::Tetromino getTetromino() const;
    int getColor() const;

    static Matrix *playfield;
    static int score;

private:
    void clearRows();
    static bool isPositionFree(int xo, int yo, tetromino::Tetromino t);
    void move(int dx, int dy);
    tetromino::Tetromino t;
    int xo, yo; // 直角坐标系
    int index;
    static std::atomic<bool> *running_flag;
};