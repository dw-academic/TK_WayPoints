#pragma once
#ifndef TKMATH_H
#define TKMATH_H 1
#define PI 3.1415926535
#define DEG180 (PI)
#define DEG360 (2*PI)
#define DEG90 (PI/2)
#include "point.h"
#include "vec2d.h"
#include <cmath>

namespace Uav
{
	class Tkmath
	{
		
	public:
		static double crossProduct(Vec2d v1, Vec2d v2);
		static double dotProduct(Vec2d v1, Vec2d v2);
		static double angle(Vec2d v1, Vec2d v2);
		static bool sameSideOfLine(Point tp, Point ref, Point a, Point b);
		static bool sameSideOfLine(Point testPoint, Point reference, Vec2d ba);
		static bool isInsideTriangle(Point tp, Point a, Point b, Point c);
	};
}
#endif