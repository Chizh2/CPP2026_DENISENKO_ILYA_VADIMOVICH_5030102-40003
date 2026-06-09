#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

class Game
{
private:
    sf::RenderWindow window;

    Board board;

public:
    Game();

    void run();
};


