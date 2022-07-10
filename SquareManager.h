#pragma once

#include "Graph.h"
#include "Engine.h"
#include "Square.h"
#include "PointSquare.h"
#include "DeathSquare.h"

#include <stdint.h>
#include<time.h>

class SquareManager
{
private:
	double _cooldown = 1;
	double _timeSinceLastSpawn = 0;

	PlayerCircles* _player;

	Square* _allSquaresStart = NULL;
	Square* _allSquaresEnd = NULL;
public:
	SquareManager(PlayerCircles* p)
	{
		srand(time(0));
		_player = p;
	}

	void SpawnSquare(float dt)
	{
		Square* sq = NULL;
		if (rand() % 2 == 1)
		{
			sq = new PointSquare();
		}
		else
		{
			sq = new DeathSquare();
		}

		if (_allSquaresStart == NULL)
		{
			_allSquaresStart = _allSquaresEnd = sq;
		}
		else
		{
			_allSquaresEnd->next = sq;
			sq->prev = _allSquaresEnd;
			_allSquaresEnd = sq;
		}
			
		_timeSinceLastSpawn = 0;
	}

	void UpdateState(float dt)
	{
		//update cooldown progress
		_timeSinceLastSpawn += dt;
		_cooldown *= 1 - dt / 100;
		if (_timeSinceLastSpawn >= _cooldown)
			SpawnSquare(dt);

		//update all squares
		Square* iter = _allSquaresStart;
		while (iter != NULL)
		{
			(*iter).UpdateState(dt);
			if ((*iter).CheckCollision(_player))
			{
				if (iter == _allSquaresStart && iter == _allSquaresEnd)
				{
					_allSquaresStart = _allSquaresEnd = iter = NULL;
				}
				else if (iter == _allSquaresStart)
				{
					_allSquaresStart = iter->next;
					free(iter);
					iter = _allSquaresStart;
				}
				else if (iter == _allSquaresEnd)
				{
					_allSquaresEnd = iter->prev;
					free(iter);
					_allSquaresEnd->next = iter = NULL;
				}
				else
				{
					iter->prev->next = iter->next;
					iter->next->prev = iter->prev;
					Square* mem = iter;
					iter = iter->next;
					free(mem);
				}
			}
			else
			{
				iter = iter->next;
			}
		}
	}

	void Draw()
	{
		Square* iter = _allSquaresStart;
		while (iter != NULL)
		{
			(*iter).Draw();
			iter = iter->next;
		}
	}
};

