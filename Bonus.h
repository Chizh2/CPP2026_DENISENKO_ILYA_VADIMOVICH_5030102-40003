#pragma once
#include <SFML/Graphics.hpp>

enum class BonusType{
    BiggerPaddle,
    SmallerPaddle,
    FasterBall,
    SlowerBall,
    StickyBall,
    BottomShield,
    RandomDirection
};

class Bonus{
private:
    sf::RectangleShape shape;

public:
    BonusType type;
    bool active;

    Bonus(float x, float y, BonusType type);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds();
};

