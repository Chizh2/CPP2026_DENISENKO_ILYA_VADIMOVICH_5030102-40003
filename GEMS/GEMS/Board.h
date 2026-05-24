#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Cell.h"

class Board {
private:
    static const int W = 8;
    static const int H = 8;
    sf::Vector2i selectedCell;
    bool hasSelection = false;
    static const int SIZE = 80;

    Cell board[H][W];

    bool selected = false;
    sf::Vector2i sel;

public:
    Board();

    void draw(sf::RenderWindow& w);
    void handleClick(int mx, int my);

    bool inside(int x, int y);
    bool isNeighbor(int x1, int y1, int x2, int y2);

    void swap(int x1, int y1, int x2, int y2);
    bool hasMatchAfterSwap(int x1, int y1, int x2, int y2);

    void clearStartMatches();
    void process();
    bool remove();
    void collapse();
    void refill();

    void findGroup(int x, int y, Color c, bool vis[H][W], std::vector<sf::Vector2i>& g);

    void spawnBonus(int x, int y);

    void setColor(int x, int y, Color c);
    Color getColor(int x, int y);

    sf::Color toSF(Color c);
};
