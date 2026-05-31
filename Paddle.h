#pragma once
#include <SFML/Graphics.hpp>

class Paddle{
private:
    sf::RectangleShape shape;
    float speed;

public:
    Paddle(float x, float y);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds();

    void changeSize(float factor);
};
