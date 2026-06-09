#include "Bonus.h"
#include "Board.h"
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

void PaintBonusCell::activate(Board& board, int x, int y) {
    Color sourceColor = getColor();
    board.setGem(x, y, sourceColor);
    std::vector<sf::Vector2i> candidates;
    for (int dy = -3; dy <= 3; dy++) {
        for (int dx = -3; dx <= 3; dx++) {
            int nx = x + dx;
            int ny = y + dy;

            if (!board.inside(nx, ny)) {
                continue;
            }

            if (nx == x && ny == y) {
                continue;
            }

            if (dx * dx + dy * dy > 9) {
                continue;
            }

            if (std::abs(dx) + std::abs(dy) == 1) {
                continue;
            }

            candidates.push_back({ nx, ny });
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(candidates.begin(), candidates.end(), gen);
    std::vector<sf::Vector2i> chosen;

    for (auto& p : candidates) {
        bool ok = true;
        for (auto& q : chosen) {
            if (board.isNeighbor(p.x, p.y, q.x, q.y)) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            continue;
        }

        board.setColor(p.x, p.y, sourceColor);
        chosen.push_back(p);

        if (chosen.size() == 2) {
            break;
        }
    }
}

void BombBonusCell::activate(Board& board, int x, int y) {
    board.setEmpty(x, y);
    std::vector<sf::Vector2i> candidates;
    for (int yy = 0; yy < board.height(); yy++) {
        for (int xx = 0; xx < board.width(); xx++) {
            if (xx == x && yy == y) {
                continue;
            }

            if (board.getColor(xx, yy) != Color::Empty) {
                candidates.push_back({ xx, yy });
            }
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(candidates.begin(), candidates.end(), gen);
    int destroyed = 1;
    for (auto& p : candidates) {
        board.setEmpty(p.x, p.y);
        destroyed++;

        if (destroyed == 5) {
            break;
        }
    }
}