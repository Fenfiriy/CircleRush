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

	double _size = 25;
	double _velocity_x, _velocity_y;
	double _angle, _angVel;

	gPoint _corns[4] = { {0,0}, {0,0}, {0,0}, {0,0} };

	virtual void _OnCollision(PlayerCircles* p) {};
	
	virtual uint32_t _GetColor()
	{
		return RED;
	};

public:
	Square* next = NULL;
	Square* prev = NULL;

	Square()
	{
		int side = rand() % 4;
		int x = rand() % SCREEN_WIDTH, y = rand() % SCREEN_HEIGHT;
		_angle = rand() % 360;
		_angVel = rand() % 360;

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

		_velocity_x = (SCREEN_WIDTH / 2 - pos.x) / ttc;
		_velocity_y = (SCREEN_HEIGHT / 2 - pos.y) / ttc;
	}

	void UpdateState(float dt)
	{
		//update position
		pos.x += _velocity_x * dt;
		pos.y += _velocity_y * dt;

		//update angle
		_angle += _angVel * dt;

		while (_angle >= 360 || _angle < 0)
		{
			if (_angle < 0)
				_angle += 360;
			if (_angle >= 360)
				_angle -= 360;
		}

		UpdateSquareCorns();
	}

	bool CheckCollision(PlayerCircles* p)
	{
		//check for collision
		if ((*p).GetCircleCollision(pos, _size * 0.9))
		{
			_OnCollision(p);
			return true;
		}
		return false;
	}

	void UpdateSquareCorns()
	{
		double radAngle = _angle * std::numbers::pi / 180;

		_corns[0].x = pos.x + _size * cos(radAngle);
		_corns[0].y = pos.y + _size * sin(radAngle);
		_corns[1].x = pos.x - _size * sin(radAngle);
		_corns[1].y = pos.y + _size * cos(radAngle);
		_corns[2].x = pos.x - _size * cos(radAngle);
		_corns[2].y = pos.y - _size * sin(radAngle);
		_corns[3].x = pos.x + _size * sin(radAngle);
		_corns[3].y = pos.y - _size * cos(radAngle);
	}

	void Draw()
	{
		fillPoly(_corns, 4, _GetColor());
	}
};

