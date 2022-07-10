#pragma once

#include "Engine.h"

#define GREEN 65280
#define BLUE 255
#define RED 16711680
#define BLACK 0
#define WHITE 16777215


struct gPoint { double x, y; };

//check if (x, y) is on screen
bool onScreen(double x, double y);
//check if point is on screen
bool onScreen(gPoint &p);

//paint pixel at set coordinates to specified color
void drawPix(double x, double y, uint32_t color);
//paint pixel at set point to specified color
void drawPix(gPoint &p, uint32_t color);

//get max of x-distance and y-distance between set coords
double diagDist(double x1, double y1, double x2, double y2);
//get max of x-distance and y-distance between set points
double diagDist(gPoint &p1, gPoint &p2);



//get max of x-distance and y-distance between set coords
double dist(double x1, double y1, double x2, double y2);
//get max of x-distance and y-distance between set points
double dist(gPoint& p1, gPoint& p2);

//paint straight line from (x1, y1) to (x2, y2)
void drawLine(double x1, double y1, double x2, double y2, uint32_t color);
//paint straight line from p1 to p2
void drawLine(gPoint &p1, gPoint &p2, uint32_t color);

//draw triangle with corners at set coords
void drawTri(double x1, double y1, double x2, double y2, double x3, double y3, uint32_t color);
//draw triangle with corners at set points
void drawTri(gPoint &p1, gPoint &p2, gPoint &p3, uint32_t color);

//triple product of given coords
double triProduct(double x1, double y1, double x2, double y2, double x3, double y3);
//triple product of given points
double triProduct(gPoint &p1, gPoint &p2, gPoint &p3);

//check if coords are inside triangle
bool pointInTriangle(double x, double y, gPoint &v1, gPoint &v2, gPoint &v3);
//check if point is inside triangle
bool pointInTriangle(gPoint &pt, gPoint &v1, gPoint &v2, gPoint &v3);

//draw filled triangle with corners at set points
void fillTri(gPoint &p1, gPoint &p2, gPoint &p3, uint32_t color);

//draw polygon with corners at set points
void drawPoly(gPoint pointArray[], int pointCount, uint32_t color, bool isClosed = true);

//draw filled convex polygon with corners at set points
void fillPoly(gPoint pointArray[], int pointCount, uint32_t color);

//rotate point around another point by set angle
gPoint rotatePoint(gPoint& v, gPoint& p, double angle);
//rotate point around another point by set angle
gPoint rotatePoint(int x, int y, gPoint& p, double angle);

//rotates given array of points around another point by set angle
gPoint* rotatePoly(gPoint pointArray[], int pointCount, gPoint &p, double angle);

//draw filled circle
void fillCircle(double x, double y, double rad, uint32_t color);
//draw filled circle
void fillCircle(gPoint& cen, double rad, uint32_t color);

//draw player circles
void drawPlayer(double centDist, double rad, double angle, uint32_t color);

uint32_t reverseColor(uint32_t color);