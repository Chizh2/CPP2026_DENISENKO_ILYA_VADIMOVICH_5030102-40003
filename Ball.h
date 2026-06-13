#pragma once
#include <SFML/Graphics.hpp>

class Ball{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    float baseSpeed;
    float speedMultiplier;

    void normalizeVelocity();

public:
    Ball(float x, float y);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    void reverseX();
    void reverseY();

    void setVelocity(sf::Vector2f v);
    sf::Vector2f getVelocity() const;

    void multiplySpeed(float factor);

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;

    sf::FloatRect getBounds() const;
};
