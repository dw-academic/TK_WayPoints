#pragma once
#ifndef VEC2D_H
#define VEC2D_H 1
#include "point.h"

namespace Uav {
	class Vec2d {
		double originX;
		double originY;
		double x;
		double y;

	public:
		Vec2d(Point, Point);
		Vec2d(double, double, double, double);
		double getOriginX();
		double getOriginY();
		void setOriginX(double);
		void setOriginY(double);
		double getX();
		double getY();
		double getMagnitude();
		void setX(double);
		void setY(double);
	};
}

#endif