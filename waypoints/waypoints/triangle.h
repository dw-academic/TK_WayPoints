#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H 1
#include "point.h"

namespace Uav
{
	class Triangle {
		Point a;
		Point b;
		Point c;
	public:
		Triangle();
		Triangle(Point, Point, Point);
		Point getA();
		Point getB();
		Point getC();
		void set(Point a, Point b, Point c);
	};
}

#endif