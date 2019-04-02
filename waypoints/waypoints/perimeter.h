#pragma once
#ifndef PERIMETER_H
#define PERIMETER_H true

#include "node.h"
#include "vec2d.h"

#include "waypoint.h"

namespace Uav
{
	class Perimeter
	{
	public:
		Perimeter();
		void addNode(int x, int y);
		void addNode(Point p);
		void addWaypoint(int x, int y);
		void addWaypoint(Point p);

		Node* getNodeAt(int i);

		void close();
		int length();
		void createBounds();

		void fill();
		int maxX();
		int maxY();
		int minX();
		int minY();
		void createWaypoints();
		void orderWaypoints();
		void printWaypoints();

		Perimeter::~Perimeter()
		{
			delete head;
			delete tail;
			delete canvas;
			delete bounds;
			delete start;
			delete end;
		}

	private:
		bool closed;
		bool bounded;
		Node *head;
		Node *tail;

		Vec2d* bounds;
		Waypoint* start;
		Waypoint* end;
	};


}

#endif
