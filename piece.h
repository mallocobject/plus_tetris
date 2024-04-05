#pragma once

#include "tetromino.h"
#include "terminal.h"
#include <vector>

class Piece
{
public:
    using Matrix = std::vector<std::vector<int>>;

    Piece() = delete;
    Piece(tetromino::Tetromino t, int xo, int yo, int index, Matrix *playfield);
    Piece(const Piece &) = default;
    Piece(Piece &&) = default;
    Piece &operator=(const Piece &) = default;
    Piece &operator=(Piece &&) = default;
    ~Piece() = default;
    static Piece generatePiece(Matrix *playfield);
    void down();
    void left();
    void right();
    void rotate();
    bool isValid(int xo, int yo);
    std::pair<int, int> getTetroPosition(int p);
    std::pair<int, int> getPosition();
    int getIndex() const;
    tetromino::Tetromino getTetromino() const;
    int getColor() const;

    Matrix *playfield = nullptr; // x, y

private:
    void move(int dx, int dy);
    tetromino::Tetromino t;
    int xo, yo; // 直角坐标系
    int index;
};