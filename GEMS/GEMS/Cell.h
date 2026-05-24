#pragma once

enum class Color {
    Red,
    Green,
    Blue,
    Yellow,
    Purple,
    Empty
};

enum class BonusType {
    None,
    Paint,
    Bomb
};

struct Cell {
    Color color = Color::Empty;
    BonusType bonus = BonusType::None;

    bool hasBonus() const {
        return bonus != BonusType::None;
    }
};
