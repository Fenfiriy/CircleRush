#pragma once

#include "Square.h"

class DeathSquare :
    public Square
{
private:
    uint32_t _GetColor()
    {
        return BLACK;
    }

    void _OnCollision(PlayerCircles* p)
    {
        (*p).Death();
    }
};

