#include "point.h"

Uav::Point::Point(double lx=0, double ly=0)
{
	x = lx;
	y = ly;
}
Uav::Point::Point()
{
	x = 0;
	y = 0;
}
void Uav::Point::setX(double lx)
{
	x = lx;
}
void Uav::Point::setY(double ly)
{
	y = ly;
}

double Uav::Point::getX()
{
	return x;
}

double Uav::Point::getY()
{
	return y;
}