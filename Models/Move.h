#pragma once
#include <stdlib.h>

typedef int8_t POS_T;

// Структура, описывающая ход пешки
struct move_pos
{
    // Откуда
    POS_T x, y;             // from
    // Куда
    POS_T x2, y2;           // to
    // Битая пешка
    POS_T xb = -1, yb = -1; // beaten

    // Простой ход
    move_pos(const POS_T x, const POS_T y, const POS_T x2, const POS_T y2) : x(x), y(y), x2(x2), y2(y2)
    {
    }
    // Ход со взятием пешки
    move_pos(const POS_T x, const POS_T y, const POS_T x2, const POS_T y2, const POS_T xb, const POS_T yb)
        : x(x), y(y), x2(x2), y2(y2), xb(xb), yb(yb)
    {
    }

    // Сравнение ходов на равенство
    bool operator==(const move_pos &other) const
    {
        return (x == other.x && y == other.y && x2 == other.x2 && y2 == other.y2);
    }
    // Сравнение ходов на неравенство
    bool operator!=(const move_pos &other) const
    {
        return !(*this == other);
    }
};
