#pragma once

#include "Graph.h"
#include "Engine.h"

#include <stdint.h>

class PlayerCircles
{
private:
	double _centerDist;
	double _radius;
	uint32_t _color;

	double _velocity = 100;
	double _angle = 0;
	bool _goingClockwise = true;

	double _timeSinceLastChange = 0;
	double _cooldown = 0.3;

	int _score = 0;
public:
	PlayerCircles(double centerDist, double rad, uint32_t color)
	{
		_centerDist = centerDist;
		_radius = rad;
		_color = color;
	}

	bool TryChangeDirection()
	{
		if (_timeSinceLastChange < _cooldown)
			return false;
		_goingClockwise = !_goingClockwise;
		_timeSinceLastChange = 0;
		return true;
	}

	void UpdateState(float dt)
	{
		//update angle
		if (_goingClockwise)
			_angle += _velocity * dt;
		else
			_angle -= _velocity * dt;

		while (_angle >= 360 || _angle < 0)
		{
			if (_angle < 0)
				_angle += 360;
			if (_angle >= 360)
				_angle -= 360;
		}

		//update speed
		_velocity += dt;
		//update cooldown progress
		_timeSinceLastChange += dt;
	}

	uint32_t GetColor()
	{
		return _color;
	}

	/*bool GetCollision(gPoint p, )
	{
		return _color;
	}*/

	void Draw()
	{
		drawPlayer(_centerDist, _radius, _angle, _color);
	}
};

