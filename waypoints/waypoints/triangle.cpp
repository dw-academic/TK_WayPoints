#include "triangle.h"
#include <iostream>

Uav::Triangle::Triangle(Point aa, Point bb, Point cc)
{
	a = aa;
	b = bb;
	c = cc;
}
Uav::Triangle::Triangle()
{
	a = Point(0,0);
	b = Point(0, 0);
	c = Point(0, 0);
}


Uav::Point Uav::Triangle::getA()
{
	return a;
}
 Uav::Point Uav::Triangle::getB()
{
	 return b;
}
 Uav::Point Uav::Triangle::getC()
{
	 return c;
}

 void Uav::Triangle::set(Point aa, Point bb, Point cc)
 {
	 a = aa;
	 b = bb;
	 c = cc;
 }
