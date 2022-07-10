#include "Graph.h"

#include <stdlib.h>
#include <memory.h>
#include <algorithm>
#include <cmath>
#include <numbers>


gPoint screenCenter = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

//check if (x, y) is on screen
bool onScreen(double x, double y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		return true;
	return false;
}
//check if point is on screen
bool onScreen(gPoint &p)
{
	return onScreen(p.x, p.y);
}

//paint pixel at set coordinates to specified color
void drawPix(double x, double y, uint32_t color)
{
	if (onScreen(x, y))
	{
		int nx = std::rint(x), ny = std::rint(y);
		buffer[ny][nx] = color;
	}
}
//paint pixel at set point to specified color
void drawPix(gPoint &p, uint32_t color)
{
	drawPix(p.x, p.y, color);
}

//get max of x-distance and y-distance between set coords
double diagDist(double x1, double y1, double x2, double y2)
{
	return std::max(abs(x1 - x2), abs(y1 - y2));
}
//get max of x-distance and y-distance between set points
double diagDist(gPoint &p1, gPoint &p2)
{
	return diagDist(p1.x, p1.y, p2.x, p2.y);
}

//get max of x-distance and y-distance between set coords
double dist(double x1, double y1, double x2, double y2)
{
	return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
//get max of x-distance and y-distance between set points
double dist(gPoint& p1, gPoint& p2)
{
	return dist(p1.x, p1.y, p2.x, p2.y);
}

//paint straight line from (x1, y1) to (x2, y2)
void drawLine(double x1, double y1, double x2, double y2, uint32_t color)
{
	double N = diagDist(x1, y1, x2, y2);
	double newX, newY;
	for (int i = 0; i < N; i++)
	{
		double t = (N == 0 ? 0.0 : (double)i / N);
		newX = std::lerp((double)x1, (double)x2, t);
		newY = std::lerp((double)y1, (double)y2, t);
		drawPix(newX, newY, color);
	}
}
//paint straight line from p1 to p2
void drawLine(gPoint &p1, gPoint &p2, uint32_t color)
{
	drawLine(p1.x, p1.y, p2.x, p2.y, color);
}

//draw triangle with corners at set coords
void drawTri(double x1, double y1, double x2, double y2, double x3, double y3, uint32_t color)
{
	drawLine(x1, y1, x2, y2, color);
	drawLine(x1, y1, x3, y3, color);
	drawLine(x2, y2, x3, y3, color);
}
//draw triangle with corners at set points
void drawTri(gPoint &p1, gPoint &p2, gPoint &p3, uint32_t color)
{
	drawTri(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color);
}

//triple product of given coords
double triProduct(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
}
//triple product of given points
double triProduct(gPoint &p1, gPoint &p2, gPoint &p3)
{
	return triProduct(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

//check if coords are inside triangle
bool pointInTriangle(double x, double y, gPoint &v1, gPoint &v2, gPoint &v3)
{
	double d1, d2, d3;
	bool has_neg, has_pos;

	d1 = triProduct(x, y, v1.x, v1.y, v2.x, v2.y);
	d2 = triProduct(x, y, v2.x, v2.y, v3.x, v3.y);
	d3 = triProduct(x, y, v3.x, v3.y, v1.x, v1.y);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}
//check if point is inside triangle
bool pointInTriangle(gPoint &pt, gPoint &v1, gPoint &v2, gPoint &v3)
{
	return pointInTriangle(pt.x, pt.y, v1, v2, v3);
}

//draw filled triangle with corners at set points
void fillTri(gPoint &p1, gPoint &p2, gPoint &p3, uint32_t color)
{
	int minX = std::min({ p1.x, p2.x, p3.x }), maxX = std::max({ p1.x, p2.x, p3.x });
	int minY = std::min({ p1.y, p2.y, p3.y }), maxY = std::max({ p1.y, p2.y, p3.y });

	for (int i = minX; i <= maxX; i++)
	{
		bool flag = false;
		for (int j = minY; j < maxY; j++)
		{
			if (pointInTriangle(i, j, p1, p2, p3))
			{
				flag = true;
				drawPix(i, j, color);
			}
			else if (flag)
			{
				break;
			}
		}
	}
}

//draw polygon with corners at set points
void drawPoly(gPoint pointArray[], int pointCount, uint32_t color, bool isClosed)
{
	for (int i = 0; i < pointCount - 1; i++)
	{
		drawLine(pointArray[i], pointArray[i + 1], color);
	}

	if (isClosed)
	{
		drawLine(pointArray[0], pointArray[pointCount - 1], color);
	}
}

//draw filled convex polygon with corners at set points
void fillPoly(gPoint pointArray[], int pointCount, uint32_t color)
{
	for (int i = 1; i < pointCount - 1; i++)
	{
		fillTri(pointArray[0], pointArray[i], pointArray[i + 1], color);
	}
}

//rotate point around another point by set angle
gPoint rotatePoint(gPoint& v, gPoint& p, double angle)
{
	int x = v.x - p.x;
	int y = v.y - p.y;

	double radAngle = angle * std::numbers::pi / 180;
	double cosA = cos(radAngle), sinA = sin(radAngle);

	v.x = std::rintf(x * cosA - y * sinA + p.x);
	v.y = std::rintf(x * sinA + y * cosA + p.y);

	return v;
}

//rotate point around another point by set angle
gPoint rotatePoint(int x, int y, gPoint& p, double angle)
{
	int nx = x - p.x;
	int ny = y - p.y;

	double radAngle = angle * std::numbers::pi / 180;
	double cosA = cos(radAngle), sinA = sin(radAngle);

	gPoint v = {
		std::rintf(nx * cosA - ny * sinA + p.x),
		std::rintf(nx * sinA + ny * cosA + p.y) };

	return v;
}

//rotates given array of points around another point by set angle
gPoint* rotatePoly(gPoint pointArray[], int pointCount, gPoint &p, double angle)
{
	for (int i = 0; i < pointCount; i++)
	{
		rotatePoint(pointArray[i], p, angle);
	}

	return pointArray;
}

//draw filled circle
void fillCircle(double x, double y, double rad, uint32_t color)
{
	for (int i = x - rad; i <= x + rad; i++)
	{
		for (int j = y - rad; j <= y + rad; j++)
		{
			if (dist(i, j, x, y) <= rad)
				drawPix(i, j, color);
		}
	}
}
//draw filled circle
void fillCircle(gPoint& cen, double rad, uint32_t color)
{
	for (int i = cen.x - rad; i <= cen.x + rad; i++)
	{
		for (int j = cen.y - rad; j <= cen.y + rad; j++)
		{
			if (dist(i, j, cen.x, cen.y) <= rad)
				drawPix(i, j, color);
		}
	}
}

//draw player circles
void drawPlayer(double centDist, double rad, double angle, uint32_t color)
{
	double radAngle = angle * std::numbers::pi / 180;
	double x1 = screenCenter.x + centDist * cos(radAngle),
		x2 = screenCenter.x - centDist * cos(radAngle),
		y1 = screenCenter.y + centDist * sin(radAngle),
		y2 = screenCenter.y - centDist * sin(radAngle);

	fillCircle(x1, y1, rad, color);
	fillCircle(x2, y2, rad, color);
}

uint32_t reverseColor(uint32_t color)
{
	int r = (color / 65536) % 256,
		g = (color / 256) % 256,
		b = color % 256;

	uint32_t newColor = (255 - r) * 65536 + (255 - g) * 256 + (255 - b);
	return newColor;
}