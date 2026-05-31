#include "Ball.h"
#include <cmath>

Ball::Ball(float x, float y){
    shape.setRadius(8.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);

    baseSpeed = 260.f;
    speedMultiplier = 1.f;

    velocity = { baseSpeed, -baseSpeed };
}

void Ball::normalizeVelocity(){
    float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    if (length == 0.f)
        return;

    velocity.x = (velocity.x / length) * baseSpeed;
    velocity.y = (velocity.y / length) * baseSpeed;
}

void Ball::update(float dt){
    shape.move(velocity * speedMultiplier * dt);
}

void Ball::draw(sf::RenderWindow& window){
    window.draw(shape);
}

void Ball::reverseX(){
    velocity.x = -velocity.x;
}

void Ball::reverseY(){
    velocity.y = -velocity.y;
}

void Ball::setVelocity(sf::Vector2f v){
    velocity = v;
    normalizeVelocity();
}

sf::Vector2f Ball::getVelocity() const{
    return velocity;
}

void Ball::multiplySpeed(float factor){
    speedMultiplier *= factor;

    if (speedMultiplier > 1.6f) {
        speedMultiplier = 1.6f;
    }

    if (speedMultiplier < 0.6f) {
        speedMultiplier = 0.6f;
    }
}

void Ball::setPosition(sf::Vector2f pos){
    shape.setPosition(pos);
}

sf::Vector2f Ball::getPosition() const{
    return shape.getPosition();
}

sf::FloatRect Ball::getBounds() const{
    return shape.getGlobalBounds();
}
