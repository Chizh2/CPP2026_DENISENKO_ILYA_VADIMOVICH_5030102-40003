#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bonus.h"

class Game{
private:
    sf::RenderWindow window;

    Ball ball;
    Paddle paddle;

    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;

    int score;

    bool bottomShield;

    sf::Font font;
    sf::Text scoreText;

    void spawnLevel();
    void resetBall();
    void handleCollisions();
    void applyBonus(BonusType type);
    float randomAngle();

public:
    Game();
    void run();
};
