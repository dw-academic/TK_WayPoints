#include "vec2d.h"
#include <iostream>

Uav::Vec2d::Vec2d(int x1, int y1, int x2, int y2)
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
Uav::Vec2d::Vec2d()
{

}
int Uav::Vec2d::getOriginX()
{
	return originX;
}
int Uav::Vec2d::getOriginY()
{
	return originY;
}
void Uav::Vec2d::setOriginX(int ox)
{
	originX = ox;
}
void Uav::Vec2d::setOriginY(int oy)
{
	originY = oy;
}
int Uav::Vec2d::getX()
{
	return x;
}
int Uav::Vec2d::getY()
{
	return y;
}
void Uav::Vec2d::setX(int xx)
{
	x = xx;
}
void Uav::Vec2d::setY(int yy)
{
	y = yy;
}
double Uav::Vec2d::getMagnitude()
{
	return sqrt(x*x + y*y);
}