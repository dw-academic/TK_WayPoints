#include "waypoint.h"

Uav::Waypoint::Waypoint()
{
	location.setX(0);
	location.setY(0);
}
Uav::Waypoint::Waypoint(int x, int y)
{
	location.setX(x);
	location.setY(y);
}
Uav::Waypoint::Waypoint(Point p)
{
	location = p;
}

Uav::Waypoint::Waypoint(Node* n)
{
	location = n->getLocation();
}


Uav::Point Uav::Waypoint::getLocation()
{
	return location;
}

void Uav::Waypoint::swap()
{
	Point t = getLocation();
	setLocation(next->getLocation());
	next->setLocation(t);
}


void Uav::Waypoint::setLocation(int x, int y)
{
	location.setX(x);
	location.setY(y);
}
void Uav::Waypoint::setLocation(Point p)
{
	location.setX(p.getX());
	location.setY(p.getY());
}
void Uav::Waypoint::setNext(Waypoint* n)
{
	next = n;
}
Uav::Waypoint* Uav::Waypoint::getNext()
{
	return next;
}
Uav::Waypoint::~Waypoint()
{

}