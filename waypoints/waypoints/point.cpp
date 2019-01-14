#include "point.h"

Uav::Point::Point(int lx=0, int ly=0)
{
	x = lx;
	y = ly;
}
Uav::Point::Point()
{
	x = 0;
	y = 0;
}
void Uav::Point::setX(int lx)
{
	x = lx;
}
void Uav::Point::setY(int ly)
{
	y = ly;
}

int Uav::Point::getX()
{
	return x;
}

int Uav::Point::getY()
{
	return y;
}