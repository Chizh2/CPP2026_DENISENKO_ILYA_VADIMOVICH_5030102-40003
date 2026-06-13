#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bonus.h"

class Game {
private:
    static constexpr unsigned WINDOW_WIDTH = 800;
    static constexpr unsigned WINDOW_HEIGHT = 600;

    static constexpr float BLOCK_WIDTH = 78.f;
    static constexpr float BLOCK_HEIGHT = 28.f;
    static constexpr float BLOCK_GAP = 4.f;

    static constexpr float BALL_START_X = 400.f;
    static constexpr float BALL_START_Y = 300.f;

    static constexpr float PADDLE_START_X = 300.f;
    static constexpr float PADDLE_START_Y = 550.f;

    static constexpr float BALL_BASE_SPEED = 260.f;

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
