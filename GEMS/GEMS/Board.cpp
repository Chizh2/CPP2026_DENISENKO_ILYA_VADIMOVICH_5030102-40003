#include "Board.h"
#include "Bonus.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>

Color Board::randomColor() const {
    return static_cast<Color>(rand() % 5);
}

std::unique_ptr<Cell> Board::createRandomGem() const {
    return std::make_unique<GemCell>(randomColor());
}

Board::Board() {
    srand(static_cast<unsigned>(time(nullptr)));

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            board[y][x] = createRandomGem();
        }
    }

    clearStartMatches();
}

bool Board::inside(int x, int y) const {
    return x >= 0 && x < W && y >= 0 && y < H;
}

bool Board::isNeighbor(int x1, int y1, int x2, int y2) const {
    return std::abs(x1 - x2) + std::abs(y1 - y2) == 1;
}

int Board::width() const {
    return W;
}

int Board::height() const {
    return H;
}

void Board::swap(int x1, int y1, int x2, int y2) {
    std::swap(board[y1][x1], board[y2][x2]);
}

Color Board::getColor(int x, int y) const {
    if (!inside(x, y) || !board[y][x]) {
        return Color::Empty;
    }

    return board[y][x]->getColor();
}

CellType Board::getCellType(int x, int y) const {
    if (!inside(x, y) || !board[y][x]) {
        return CellType::Gem;
    }

    return board[y][x]->getType();
}

void Board::setColor(int x, int y, Color c) {
    if (!inside(x, y)) {
        return;
    }

    if (!board[y][x]) {
        board[y][x] = std::make_unique<GemCell>(c);
    }

    else {
        board[y][x]->setColor(c);
    }
}

void Board::setGem(int x, int y, Color c) {
    if (inside(x, y)) {
        board[y][x] = std::make_unique<GemCell>(c);
    }
}

void Board::setPaintBonus(int x, int y, Color c) {
    if (inside(x, y)) {
        board[y][x] = std::make_unique<PaintBonusCell>(c);
    }
}

void Board::setBombBonus(int x, int y, Color c) {
    if (inside(x, y)) {
        board[y][x] = std::make_unique<BombBonusCell>(c);
    }
}

void Board::setEmpty(int x, int y) {
    if (inside(x, y)) {
        board[y][x] = std::make_unique<GemCell>(Color::Empty);
    }
}

void Board::findGroup(int x, int y, Color c, bool vis[H][W], std::vector<sf::Vector2i>& g) {
    if (!inside(x, y)) {
        return;
    }

    if (vis[y][x]) {
        return;
    }

    if (getColor(x, y) != c || c == Color::Empty) {
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
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (vis[y][x] || getColor(x, y) == Color::Empty) {
                continue;
            }

            std::vector<sf::Vector2i> group;
            findGroup(x, y, getColor(x, y), vis, group);
            if (group.size() >= 3) {
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

    if (board[y][x] && board[y][x]->isBonus()) {
        board[y][x]->activate(*this, x, y);
        process();
        return;
    }

    if (!selected) {
        sel = { x, y };
        selectedCell = sel;
        selected = true;
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
                if (vis[y][x] || getColor(x, y) == Color:: Empty) {
                    continue;
                }

                std::vector<sf::Vector2i> group;
                findGroup(x, y, getColor(x, y), vis, group);

                if (group.size() >= 3) {
                    found = true;

                    for (auto& p : group) {
                        setGem(p.x, p.y, randomColor());
                    }
                }
            }
        }
        if (!found) {
            break;
        }
    }
}

void Board::spawnBonus(int x, int y, Color sourceColor) {
    std::vector<sf::Vector2i> places;
    for (int dy = -3; dy <= 3; dy++) {
        for (int dx = -3; dx <= 3; dx++) {
            int nx = x + dx;
            int ny = y + dy;

            if (!inside(nx, ny)) {
                continue;
            }

            if (dx * dx + dy * dy > 9) {
                continue;
            }

            places.push_back({ nx, ny });
        }
    }

    if (places.empty()) {
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(places.begin(), places.end(), gen);
    sf::Vector2i pos = places.front();

    if (rand() % 2 == 0) {
        setPaintBonus(pos.x, pos.y, sourceColor);
    }
    else {
        setBombBonus(pos.x, pos.y, sourceColor);
    }
}

bool Board::remove() {
    bool vis[H][W] = {};
    bool removed = false;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (vis[y][x] || getColor(x, y) == Color::Empty) {
                continue;
            }

            std::vector<sf::Vector2i> group;
            Color groupColor = getColor(x, y);
            findGroup(x, y, groupColor, vis, group);

            if (group.size() >= 3) {
                removed = true;
                bool makeBonus = rand() % 100 < 5;
                int sourceX = x;
                int sourceY = y;

                if (makeBonus) {
                    int idx = rand() % group.size();
                    sourceX = group[idx].x;
                    sourceY = group[idx].y;
                }

                for (auto& p : group) {
                    setEmpty(p.x, p.y);
                }

                if (makeBonus) {
                    spawnBonus(sourceX, sourceY, groupColor);
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
            if (getColor(x, y) != Color::Empty) {
                if (write != y) {
                    board[write][x] = std::move(board[y][x]);
                    board[y][x] = std::make_unique<GemCell>(Color::Empty);
                }
                write--;
            }
        }
        while (write >= 0) {
            setEmpty(x, write);
            write--;
        }
    }
}

void Board::refill() {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (getColor(x, y) == Color::Empty) {
                board[y][x] = createRandomGem();
            }
        }
    }
}

void Board::process() {
    int safety = 0;
    while (safety < 20) {
        safety++;
        bool changed = remove();
        bool hasEmpty = false;
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                if (getColor(x, y) == Color::Empty) {
                    hasEmpty = true;
                }
            }
        }

        if (!changed && !hasEmpty) {
            break;
        }

        collapse();
        refill();
    }
}

sf::Color Board::toSF(Color c) const {
    switch (c) {
    case Color::Red:
        return sf::Color::Red;

    case Color::Green:
        return sf::Color::Green;

    case Color::Blue:
        return sf::Color::Blue;

    case Color::Yellow:
        return sf::Color::Yellow;

    case Color::Purple:
        return sf::Color(180, 0, 255);

    default:
        return sf::Color::Black;
    }
}

void Board::draw(sf::RenderWindow& w) {
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            sf::RectangleShape r(sf::Vector2f(SIZE - 2, SIZE - 2));
            r.setPosition(x * SIZE, y * SIZE);
            r.setFillColor(toSF(getColor(x, y)));
            w.draw(r);

            if (board[y][x] && board[y][x]->isBonus()) {
                sf::CircleShape bonus(7);
                bonus.setPosition(x * SIZE + 10, y * SIZE + 10);
                bonus.setOutlineThickness(2);
                bonus.setOutlineColor(sf::Color::White);

                if (board[y][x]->getType() == CellType::PaintBonus) {
                    bonus.setFillColor(sf::Color::Magenta);
                }

                else if (board[y][x]->getType() == CellType::BombBonus) {
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