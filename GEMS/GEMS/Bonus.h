#pragma once
#include "Cell.h"

class Board;

class Bonus {
public:
    static void applyPaint(Board& board, int x, int y, Color source);
    static void applyBomb(Board& board, int x, int y);
};


