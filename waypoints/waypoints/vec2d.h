#pragma once
#ifndef VEC2D_H
#define VEC2D_H 1
#include "point.h"

namespace Uav {
	class Vec2d {
		int originX;
		int originY;
		int x;
		int y;

	public:
		Vec2d();
		Vec2d(Point, Point);
		Vec2d(int, int, int, int);
		int getOriginX();
		int getOriginY();
		void setOriginX(int);
		void setOriginY(int);
		int getX();
		int getY();
		double getMagnitude();
		void setX(int);
		void setY(int);
	};
}

#endif