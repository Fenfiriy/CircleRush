#pragma once

#include "Square.h"

class PointSquare :
    public Square
{
private:
    uint32_t _GetColor()
    {
        return WHITE;
    }

    void _OnCollision(PlayerCircles* p)
    {
        (*p).IncScore();
    }
};

