#pragma once
#include <SFML/Graphics.hpp>

enum class BlockType{
    Normal,
    Indestructible,
    Speed
};

class Block{
public:
    sf::RectangleShape shape;

    BlockType type;

    int hp;
    int maxHp;

    bool destroyed;
    bool hasBonus;

    Block(float x, float y, BlockType type, int hp);

    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    void updateColor();
};
