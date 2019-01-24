#pragma once
#ifndef WAYPOINT_H 
#define WAYPOINT_H 1

#include "point.h"
#include "node.h"

namespace Uav {
	class Waypoint // similar to a node, but kept separate for potential expansion
	{
	public:
		Waypoint();
		Waypoint(int x, int y);
		Waypoint(Point);
		Waypoint(Node*);
		~Waypoint();
		Point getLocation();
		void setNext(Waypoint*);
		Waypoint* getNext();
		void swap();

		void setLocation(int x, int y);
		void setLocation(Point);
	private:
		Point location;
		Waypoint *next;
	};
}


#endif