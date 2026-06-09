#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
class Board;

enum class Color {
    Red,
    Green,
    Blue,
    Yellow,
    Purple,
    Empty
};

enum class CellType {
    Gem,
    PaintBonus,
    BombBonus
};

class Cell {
protected:
    Color color;

public:
    Cell(Color c = Color::Empty) : color(c) {}
    virtual ~Cell() = default;
    Color getColor() const {
        return color;
    }

    void setColor(Color c) {
        color = c;
    }

    virtual CellType getType() const {
        return CellType::Gem;
    }

    virtual bool isBonus() const {
        return false;
    }
    virtual void activate(Board& board, int x, int y) {}
};

class GemCell : public Cell {
public:
    GemCell(Color c = Color::Empty) : Cell(c) {}

    CellType getType() const override {
        return CellType::Gem;
    }
};
