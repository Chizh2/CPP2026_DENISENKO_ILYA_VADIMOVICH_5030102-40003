#include "Block.h"
#include <cstdlib>

Block::Block(float x, float y, BlockType type, int hp){
    this->type = type;
    this->hp = hp;
    this->maxHp = hp;
    this->destroyed = false;
    this->hasBonus = (rand() % 100 < 15);

    shape.setSize({ 78.f, 28.f });
    shape.setPosition(x, y);
    shape.setOutlineThickness(0.f);

    updateColor();
}

void Block::updateColor(){
    if (type == BlockType::Indestructible){
        shape.setFillColor(sf::Color(120, 120, 120));
        return;
    }

    if (hp >= 3) {
        shape.setFillColor(sf::Color(60, 200, 60));
    }
    else if (hp == 2) {
        shape.setFillColor(sf::Color(240, 210, 60));
    }
    else {
        shape.setFillColor(sf::Color(220, 70, 70));
    }
}

void Block::draw(sf::RenderWindow& window)
{
    if (!destroyed)
        window.draw(shape);
}

sf::FloatRect Block::getBounds() const
{
    return shape.getGlobalBounds();
}
