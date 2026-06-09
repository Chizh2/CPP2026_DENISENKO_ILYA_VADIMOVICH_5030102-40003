#pragma once

#include "Cell.h"

class PaintBonusCell : public Cell {
public:
    PaintBonusCell(Color c) : Cell(c) {}

    CellType getType() const override {
        return CellType::PaintBonus;
    }

    bool isBonus() const override {
        return true;
    }

    void activate(Board& board, int x, int y) override;
};

class BombBonusCell : public Cell {
public:
    BombBonusCell(Color c) : Cell(c) {}

    CellType getType() const override {
        return CellType::BombBonus;
    }

    bool isBonus() const override {
        return true;
    }

    void activate(Board& board, int x, int y) override;
};