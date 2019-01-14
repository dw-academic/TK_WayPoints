#pragma once
#ifndef POINT_H
#define POINT_H 1
namespace Uav {
	class Point {
		int x;
		int y;

	public:
		Point(int, int);
		Point();
		int getX();
		int getY();
		void setX(int);
		void setY(int);
	};
}
#endif
