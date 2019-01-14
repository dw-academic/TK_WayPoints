#include "vec2d.h"
#include <iostream>

Uav::Vec2d::Vec2d(double x1, double y1, double x2, double y2)
{
	setOriginX(x1);
	setOriginY(y1);
	setX(x2 - x1);
	setY(y2 - y1);
}
Uav::Vec2d::Vec2d(Point p1, Point p2)
{
	setOriginX(p1.getX());
	setOriginY(p1.getY());
	setX(p2.getX() - p1.getX());
	setY(p2.getY() - p1.getY());
}
double Uav::Vec2d::getOriginX()
{
	return originX;
}
double Uav::Vec2d::getOriginY()
{
	return originY;
}
void Uav::Vec2d::setOriginX(double ox)
{
	originX = ox;
}
void Uav::Vec2d::setOriginY(double oy)
{
	originY = oy;
}
double Uav::Vec2d::getX()
{
	return x;
}
double Uav::Vec2d::getY()
{
	return y;
}
void Uav::Vec2d::setX(double xx)
{
	x = xx;
}
void Uav::Vec2d::setY(double yy)
{
	y = yy;
}
double Uav::Vec2d::getMagnitude()
{
	return sqrt(x*x + y*y);
}