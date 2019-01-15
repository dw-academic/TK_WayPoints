#pragma once
#ifndef PERIMETER_H
#define PERIMETER_H true

#include "node.h"
#include "vec2d.h"
#include "canvas.h"
#include "waypoint.h"

namespace Uav
{
	class Perimeter
	{
	public:
		Perimeter(Canvas*);
		~Perimeter();
		void addNode(int x, int y);
		void addNode(Point p);
		void deleteLastNode();
		Node* getNodeAt(int i);
		void showNodes();
		void close();
		int length();
		void createBounds();
		void showBounds();
		void fill();
		int maxX();
		int maxY();
		int minX();
		int minY();
		void createWaypoints();

	private:
		bool closed;
		Node *head;
		Node *tail;
		Canvas* canvas;
		Vec2d* bounds;
		Waypoint* start;
		Waypoint* end;
	};


}

#endif