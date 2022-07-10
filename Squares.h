#pragma once

#include "Graph.h"
#include "Engine.h"
#include "PlayerCircles.h"

#include <stdlib.h>

double ttc = 1.0;

class Square
{
private:
	gPoint pos = { 0, 0 };

	double _size;
	double _velocity_x, _velocity_y;
	double _angle, _angVel;

	uint32_t _color;
public:
	Square()
	{
		int side = rand() % 4;
		int x = rand() % SCREEN_WIDTH, y = rand() % SCREEN_HEIGHT;
		_angle = rand() % 360;
		_angVel = rand() % 360 - 180;

		switch (side)
		{
		case 0:
			y = 0;
			break;
		case 1:
			x = SCREEN_WIDTH;
			break;
		case 2:
			y = SCREEN_HEIGHT;
			break;
		case 4:

		default:
			x = 0;
			break;
		}

		pos.x = x;
		pos.y = y;

		_velocity_x = (screenCenter.x - pos.x) / ttc;
		_velocity_y = (screenCenter.y - pos.y) / ttc;
	}

	void UpdateState(float dt)
	{
		//update angle
		_angle += _angVel * dt;

		while (_angle >= 360 || _angle < 0)
		{
			if (_angle < 0)
				_angle += 360;
			if (_angle >= 360)
				_angle -= 360;
		}

		//check for collision

	}
};

