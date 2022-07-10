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
	bool _isAlive = true;

	gPoint _cents[2] = { {0, 0}, {0,0} };
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

		UpdateCircleCents();
	}

	uint32_t GetColor()
	{
		return _color;
	}

	void UpdateCircleCents()
	{
		double radAngle = _angle * std::numbers::pi / 180;
		double x1 = screenCenter.x + _centerDist * cos(radAngle),
			x2 = screenCenter.x - _centerDist * cos(radAngle),
			y1 = screenCenter.y + _centerDist * sin(radAngle),
			y2 = screenCenter.y - _centerDist * sin(radAngle);

		_cents[0].x = x1;
		_cents[0].y = y1;
		_cents[1].x = x2;
		_cents[1].y = y2;
	}

	bool GetCircleCollision(gPoint p, double rad)
	{
		bool res = (dist(p, _cents[0]) <= _radius + rad) || (dist(p, _cents[1]) <= _radius + rad);

		return res;
	}

	void Draw()
	{
		fillCircle(_cents[0].x, _cents[0].y, _radius, _color);
		fillCircle(_cents[1].x, _cents[1].y, _radius, _color);

		DrawScore(_score, RED);
	}

	void IncScore()
	{
		_score++;
	}
	bool IsAlive()
	{
		return _isAlive;
	}

	void Death()
	{
		_isAlive = false;
	}
};

