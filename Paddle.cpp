#include "Paddle.h"

Paddle::Paddle(float x, float y){
    shape.setSize({ 120.f, 20.f });
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);

    speed = 500.f;
}

void Paddle::update(float dt){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        shape.move(-speed * dt, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        shape.move(speed * dt, 0);
    }

    if (shape.getPosition().x < 0) {
        shape.setPosition(0, shape.getPosition().y);
    }

    if (shape.getPosition().x + shape.getSize().x > 800) {
        shape.setPosition(800 - shape.getSize().x, shape.getPosition().y);
    }
}

void Paddle::draw(sf::RenderWindow& window){
    window.draw(shape);
}

sf::FloatRect Paddle::getBounds(){
    return shape.getGlobalBounds();
}

void Paddle::changeSize(float factor){
    auto s = shape.getSize();
    s.x *= factor;

    if (s.x < 50) s.x = 50;
    if (s.x > 250) s.x = 250;

    shape.setSize(s);
}
