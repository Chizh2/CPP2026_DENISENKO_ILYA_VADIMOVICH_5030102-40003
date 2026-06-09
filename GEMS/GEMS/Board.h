#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Cell.h"

class Board {
private:
    static const int W = 8;
    static const int H = 8;
    static const int SIZE = 80;

    std::unique_ptr<Cell> board[H][W];
    bool selected = false;
    bool hasSelection = false;

    sf::Vector2i sel;
    sf::Vector2i selectedCell;

    Color randomColor() const;
    std::unique_ptr<Cell> createRandomGem() const;
public:
    Board();
    void draw(sf::RenderWindow& w);
    void handleClick(int mx, int my);
    bool inside(int x, int y) const;
    bool isNeighbor(int x1, int y1, int x2, int y2) const;
    void swap(int x1, int y1, int x2, int y2);
    bool hasMatchAfterSwap(int x1, int y1, int x2, int y2);
    void clearStartMatches();
    void process();
    bool remove();
    void collapse();
    void refill();
    void findGroup(int x, int y, Color c, bool vis[H][W], std::vector<sf::Vector2i>& g);
    void spawnBonus(int x, int y, Color sourceColor);
    void setColor(int x, int y, Color c);

    Color getColor(int x, int y) const;
    CellType getCellType(int x, int y) const;

    void setGem(int x, int y, Color c);
    void setPaintBonus(int x, int y, Color c);
    void setBombBonus(int x, int y, Color c);
    void setEmpty(int x, int y);

    int width() const;
    int height() const;

    sf::Color toSF(Color c) const;
};
