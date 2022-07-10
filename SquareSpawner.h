#pragma once

#include "Graph.h"
#include "Engine.h"
#include "Squares.h"

#include <stdint.h>
#include <map>

class SquareManager
{
private:
	double _cooldown = 0.7;
	double _timeSinceLastSpawn = 0;

	Square * _allSquares;
public:
	SquareManager()
	{
	}

	bool TrySpawnSquare(float dt)
	{
		if (_timeSinceLastSpawn >= _cooldown)
		{
			Square sq();
			
			_timeSinceLastSpawn = 0;
		}
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
};

