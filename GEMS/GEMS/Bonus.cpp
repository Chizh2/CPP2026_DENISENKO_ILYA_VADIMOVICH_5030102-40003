#include "Bonus.h"
#include "Board.h"
#include <cstdlib>
#include <cmath>

static bool isNeighbor(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2) == 1;
}

void Bonus::applyPaint(Board& board, int x, int y, Color source) {
    board.setColor(x, y, source);

    int cnt = 0;

    while (cnt < 2) {
        int rx = x + (rand() % 7 - 3);
        int ry = y + (rand() % 7 - 3);

        if (!board.inside(rx, ry)) {
            continue;
        }
        if (isNeighbor(x, y, rx, ry)) {
            continue;
        }

        board.setColor(rx, ry, source);
        cnt++;
    }
}

void Bonus::applyBomb(Board& board, int x, int y) {
    board.setColor(x, y, Color::Empty);

    int killed = 1;

    while (killed < 5) {
        int rx = rand() % 8;
        int ry = rand() % 8;

        if (board.getColor(rx, ry) != Color::Empty) {
            board.setColor(rx, ry, Color::Empty);
            killed++;
        }
    }
}
