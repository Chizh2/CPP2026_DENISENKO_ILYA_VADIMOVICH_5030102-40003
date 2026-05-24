#include "Board.h"
#include "Bonus.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>

Board::Board() {
    srand((unsigned)time(nullptr));

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            board[y][x].color = (Color)(rand() % 5);
            board[y][x].bonus = BonusType::None;
        }
    }
    clearStartMatches();
}

bool Board::inside(int x, int y) {
    return x >= 0 && x < W && y >= 0 && y < H;
}

bool Board::isNeighbor(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2) == 1;
}

void Board::swap(int x1, int y1, int x2, int y2) {
    std::swap(board[y1][x1], board[y2][x2]);
}

Color Board::getColor(int x, int y) {
    return board[y][x].color;
}

void Board::setColor(int x, int y, Color c) {
    board[y][x].color = c;
}

void Board::findGroup(int x, int y, Color c, bool vis[H][W], std::vector<sf::Vector2i>& g) {
    if (!inside(x, y)) {
        return;
    }
    if (vis[y][x]) {
        return;
    }
    if (board[y][x].color != c) {
        return;
    }

    vis[y][x] = true;
    g.push_back({ x, y });

    findGroup(x + 1, y, c, vis, g);
    findGroup(x - 1, y, c, vis, g);
    findGroup(x, y + 1, c, vis, g);
    findGroup(x, y - 1, c, vis, g);
}

bool Board::hasMatchAfterSwap(int x1, int y1, int x2, int y2) {
    swap(x1, y1, x2, y2);

    bool vis[H][W] = {};
    std::vector<sf::Vector2i> g;

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {

            if (vis[y][x] || board[y][x].color == Color::Empty) {
                continue;
            }

            g.clear();
            findGroup(x, y, board[y][x].color, vis, g);

            if (g.size() >= 3) {
                swap(x1, y1, x2, y2);
                return true;
            }
        }
    }

    swap(x1, y1, x2, y2);
    return false;
}

void Board::handleClick(int mx, int my) {
    int x = mx / SIZE;
    int y = my / SIZE;

    if (!inside(x, y)) {
        return;
    }

    if (board[y][x].bonus != BonusType::None) {

        //PAINT
        if (board[y][x].bonus == BonusType::Paint) {
            Color c = board[y][x].color;

            board[y][x].color = c;

            int painted = 0;

            while (painted < 2) {
                int rx = rand() % W;
                int ry = rand() % H;

                if (abs(rx - x) + abs(ry - y) <= 1) {
                    continue;
                }

                board[ry][rx].color = c;

                painted++;
            }
        }

        //BOMB 
        else if (board[y][x].bonus == BonusType::Bomb) {
            int destroyed = 0;

            board[y][x].color = Color::Empty;
            board[y][x].bonus = BonusType::None;

            destroyed++;

            while (destroyed < 5) {
                int rx = rand() % W;
                int ry = rand() % H;

                if (board[ry][rx].color == Color::Empty) {
                    continue;
                }

                board[ry][rx].color = Color::Empty;
                board[ry][rx].bonus = BonusType::None;

                destroyed++;
            }
        }

        board[y][x].bonus = BonusType::None;

        process();
        return;
    }

    if (!selected) {
        sel = {x, y};

        selected = true;

        selectedCell = sel;
        hasSelection = true;

        return;
    }

    if (isNeighbor(sel.x, sel.y, x, y)) {
        if (hasMatchAfterSwap(sel.x, sel.y, x, y)) {
            swap(sel.x, sel.y, x, y);

            process();
        }
    }

    selected = false;
    hasSelection = false;
}

void Board::clearStartMatches() {
    while (true) {

        bool vis[H][W] = {};
        bool found = false;

        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {

                if (vis[y][x]) {
                    continue;
                }

                std::vector<sf::Vector2i> group;
                findGroup(x, y, board[y][x].color, vis, group);

                if (group.size() >= 3) {

                    found = true;

                    for (auto& p : group) {
                        board[p.y][p.x].color = (Color)(rand() % 5);
                        board[p.y][p.x].bonus = BonusType::None;
                    }
                }
            }
        }

        if (!found){
            break;
        }
    }
}

bool Board::remove() {
    bool vis[H][W] = {};
    bool removed = false;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {

            if (vis[y][x]) {
                continue;
            }
            if (board[y][x].color == Color::Empty) {
                continue;
            }

            std::vector<sf::Vector2i> group;

            findGroup(x, y, board[y][x].color, vis, group);

            if (group.size() >= 3) {
                removed = true;
                bool makeBonus = (rand() % 100 < 5);

                int bonusX = -1;
                int bonusY = -1;

                if (makeBonus) {
                    int idx = rand() % group.size();

                    bonusX = group[idx].x;
                    bonusY = group[idx].y;
                }

                for (auto& p : group) {
                    board[p.y][p.x].color = Color::Empty;
                    board[p.y][p.x].bonus = BonusType::None;
                }

                if (makeBonus) {
                    board[bonusY][bonusX].color = (Color)(rand() % 5);

                    board[bonusY][bonusX].bonus =
                        (rand() % 2 == 0) ? BonusType::Paint: BonusType::Bomb;
                }
            }
        }
    }
    return removed;
}

void Board::collapse() {
    for (int x = 0; x < W; x++) {
        int write = H - 1;

        for (int y = H - 1; y >= 0; y--) {
            if (board[y][x].color != Color::Empty) {
                board[write][x].color = board[y][x].color;
                board[write][x].bonus = board[y][x].bonus;
                write--;
            }
        }

        while (write >= 0) {
            board[write][x].color = Color::Empty;
            board[write][x].bonus = BonusType::None;
            write--;
        }
    }
}

void Board::refill() {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (board[y][x].color == Color::Empty) {
                board[y][x].color = (Color)(rand() % 5);
                board[y][x].bonus = BonusType::None;
            }
        }
    }
}

void Board::process() {
    int safety = 0;

    while (safety < 20) {
        safety++;

        bool changed = remove();
        collapse();
        refill();

        bool vis[H][W] = {};
        bool hasGroups = false;

        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {

                if (vis[y][x]) continue;
                if (board[y][x].color == Color::Empty) {
                    continue;
                }

                std::vector<sf::Vector2i> group;

                findGroup(x, y, board[y][x].color, vis, group);

                if (group.size() >= 3) {
                    hasGroups = true;
                }
            }
        }

        if (!changed && !hasGroups) {
            break;
        }
    }
}

sf::Color Board::toSF(Color c) {
    switch (c) {
    case Color::Red: return sf::Color::Red;
    case Color::Green: return sf::Color::Green;
    case Color::Blue: return sf::Color::Blue;
    case Color::Yellow: return sf::Color::Yellow;
    case Color::Purple: return sf::Color(180, 0, 255);
    default: return sf::Color::Black;
    }
}

void Board::draw(sf::RenderWindow& w) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {

            sf::RectangleShape r(sf::Vector2f(SIZE - 2, SIZE - 2));
            r.setPosition(x * SIZE, y * SIZE);
            r.setFillColor(toSF(board[y][x].color));

            w.draw(r);
            if (board[y][x].bonus != BonusType::None) {

                sf::CircleShape bonus(7);
                bonus.setPosition(x * SIZE + 10, y * SIZE + 10);

                bonus.setOutlineThickness(2);
                bonus.setOutlineColor(sf::Color::White);
                if (board[y][x].bonus == BonusType::Paint) {
                    bonus.setFillColor(sf::Color::Magenta);
                }
                else if (board[y][x].bonus == BonusType::Bomb) {
                    bonus.setFillColor(sf::Color::Black);
                }

                w.draw(bonus);
            }

            if (hasSelection && x == selectedCell.x && y == selectedCell.y) {
                sf::RectangleShape outline(sf::Vector2f(SIZE - 2, SIZE - 2));
                outline.setPosition(x * SIZE, y * SIZE);
                outline.setFillColor(sf::Color::Transparent);
                outline.setOutlineThickness(4);
                outline.setOutlineColor(sf::Color::White);

                w.draw(outline);
            }
        }
    }
}
