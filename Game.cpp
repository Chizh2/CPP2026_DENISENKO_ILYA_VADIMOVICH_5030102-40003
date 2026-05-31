#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Game::Game() :
    window(sf::VideoMode(800, 600), "Arkanoid"),
    ball(400.f, 300.f),
    paddle(300.f, 550.f),
    score(0),
    bottomShield(false){
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    spawnLevel();

    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
}

void Game::run(){
    sf::Clock clock;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        paddle.update(dt);
        ball.update(dt);

        for (auto& b : bonuses) {
            b.update(dt);
        }

        handleCollisions();

        if (ball.getBounds().top > 600.f){
            if (bottomShield){
                bottomShield = false;
                ball.reverseY();
            }
            else{
                score -= 1;
                resetBall();
            }
        }

        scoreText.setString("Score: " + std::to_string(score));

        window.clear(sf::Color::Black);

        ball.draw(window);
        paddle.draw(window);

        for (auto& b : blocks) {
            b.draw(window);
        }

        for (auto& b : bonuses) {
            b.draw(window);
        }

        window.draw(scoreText);
        window.display();
    }
}

void Game::spawnLevel(){
    blocks.clear();

    const float bw = 78.f;
    const float bh = 28.f;
    const float gap = 4.f;

    for (int y = 0; y < 5; y++){
        for (int x = 0; x < 10; x++){
            BlockType type = BlockType::Normal;

            int r = rand() % 100;

            if (r < 10)
                type = BlockType::Indestructible;
            else if (r < 25)
                type = BlockType::Speed;

            int hp = 1 + (rand() % 3);

            if (type == BlockType::Indestructible)
                hp = 999;

            blocks.emplace_back(x * (bw + gap), y * (bh + gap), type, hp);
        }
    }
}

void Game::resetBall(){
    ball.setPosition({ 400.f, 300.f });
    ball.setVelocity({ 260.f, -260.f });
}

float Game::randomAngle(){
    return (rand() % 120 + 30) * 3.1415926f / 180.f;
}

void Game::applyBonus(BonusType type){
    switch (type){
    case BonusType::BiggerPaddle:
        paddle.changeSize(1.3f);
        break;

    case BonusType::SmallerPaddle:
        paddle.changeSize(0.7f);
        break;

    case BonusType::FasterBall:
        ball.multiplySpeed(1.2f);
        break;

    case BonusType::SlowerBall:
        ball.multiplySpeed(0.8f);
        break;

    case BonusType::StickyBall:
        ball.setVelocity({ 0.f, 0.f });
        break;

    case BonusType::BottomShield:
        bottomShield = true;
        break;

    case BonusType::RandomDirection:{
        float speed = 260.f;
        float a = randomAngle();
        ball.setVelocity({ cos(a) * speed, -sin(a) * speed });
        break;
    }
    }
}

void Game::handleCollisions(){
    auto b = ball.getBounds();

    if (b.left <= 0){
        ball.setPosition({ 1.f, b.top });
        ball.reverseX();
    }

    if (b.left + b.width >= 800){
        ball.setPosition({ 800.f - b.width - 1.f, b.top });
        ball.reverseX();
    }

    if (b.top <= 0){
        ball.setPosition({ b.left, 1.f });
        ball.reverseY();
    }

    if (b.intersects(paddle.getBounds())){
        ball.setPosition({ b.left, paddle.getBounds().top - b.height - 1.f });
        ball.reverseY();
    }

    for (auto& block : blocks){
        if (block.destroyed) {
            continue;
        }

        if (!b.intersects(block.getBounds())) {
            continue;
        }
        score += 1;

        sf::FloatRect bb = block.getBounds();

        float ballCX = b.left + b.width / 2.f;
        float ballCY = b.top + b.height / 2.f;

        float blockCX = bb.left + bb.width / 2.f;
        float blockCY = bb.top + bb.height / 2.f;

        float dx = ballCX - blockCX;
        float dy = ballCY - blockCY;

        if (std::abs(dx) > std::abs(dy)){
            ball.reverseX();

            if (dx > 0) {
                ball.setPosition({ bb.left + bb.width + 1.f, b.top });
            }
            else {
                ball.setPosition({ bb.left - b.width - 1.f, b.top });
            }
        }
        else{
            ball.reverseY();

            if (dy > 0) {
                ball.setPosition({ b.left, bb.top + bb.height + 1.f });
            }
            else {
                ball.setPosition({ b.left, bb.top - b.height - 1.f });
            }
        }

        bool spawnBonus = false;

        if (block.type != BlockType::Indestructible){
            block.hp--;
            block.updateColor();

            if (block.hp <= 0){
                spawnBonus = block.hasBonus;
                block.destroyed = true;
            }

            if (block.type == BlockType::Speed){
                ball.multiplySpeed(1.15f);
            }
        }

        if (spawnBonus){
            int r = rand() % 100;

            BonusType type;

            if (r < 20) type = BonusType::BiggerPaddle;
            else if (r < 40) type = BonusType::SmallerPaddle;
            else if (r < 60) type = BonusType::FasterBall;
            else if (r < 75) type = BonusType::SlowerBall;
            else if (r < 85) type = BonusType::StickyBall;
            else if (r < 95) type = BonusType::BottomShield;
            else type = BonusType::RandomDirection;

            bonuses.emplace_back(bb.left + bb.width / 2.f,bb.top + bb.height / 2.f,type);
        }

        break;
    }
    
    for (auto& bonus : bonuses){
        if (!bonus.active) {
            continue;
        }

        if (bonus.getBounds().intersects(paddle.getBounds())){
            applyBonus(bonus.type);
            bonus.active = false;
        }
    }
}
