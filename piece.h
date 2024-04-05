#pragma once

#include "define.h"

class Piece
{
public:
    Piece() = delete;
    Piece(int x, int y, terminal::Color color, int index) : x(x), y(y), color(color), index(index) {}
    Piece(const Piece &) = default;
    Piece(Piece &&) = default;
    Piece &operator=(const Piece &) = default;
    Piece &operator=(Piece &&) = default;
    ~Piece() = default;
    static Piece generatePiece();
    void down();
    void left();
    void right();
    void rotate();
    bool isValid(int x, int y);

private:
    void move(int dx, int dy);
    int x, y;
    terminal::Color color;
    int index;
};