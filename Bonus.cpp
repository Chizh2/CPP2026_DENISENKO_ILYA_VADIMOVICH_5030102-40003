#include "Bonus.h"

Bonus::Bonus(float x, float y, BonusType type){
    this->type = type;
    active = true;

    shape.setSize({ 18.f, 18.f });

    switch (type)
    {
    case BonusType::BiggerPaddle:
        shape.setFillColor(sf::Color::Green);
        break;

    case BonusType::SmallerPaddle:
        shape.setFillColor(sf::Color::Red);
        break;

    case BonusType::FasterBall:
        shape.setFillColor(sf::Color::Yellow);
        break;

    case BonusType::SlowerBall:
        shape.setFillColor(sf::Color::Cyan);
        break;

    case BonusType::StickyBall:
        shape.setFillColor(sf::Color::Magenta);
        break;

    case BonusType::BottomShield:
        shape.setFillColor(sf::Color(255, 165, 0));
        break;

    case BonusType::RandomDirection:
        shape.setFillColor(sf::Color::White);
        break;
    }

    shape.setPosition(x + 10.f, y + 30.f);
}

void Bonus::update(float dt){
    shape.move(0.f, 220.f * dt);
}

void Bonus::draw(sf::RenderWindow& window){
    if (active)
        window.draw(shape);
}

sf::FloatRect Bonus::getBounds(){
    return shape.getGlobalBounds();
}
