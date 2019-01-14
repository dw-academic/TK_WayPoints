#include "node.h"

Uav::Node::Node()
{
	location.setX(0);
	location.setY(0);
}
Uav::Node::Node(int x, int y)
{
	location.setX(x);
	location.setY(y);
}
Uav::Node::Node(Point p)
{
	location = p;
}
Uav::Point Uav::Node::getLocation()
{
	return location;
}
void Uav::Node::setLocation(int x, int y)
{
	location.setX(x);
	location.setY(y);
}
void Uav::Node::setLocation(Point p)
{
	location.setX(p.getX());
	location.setY(p.getY());
}
void Uav::Node::setNext(Node* n)
{
	next = n;
}
Uav::Node* Uav::Node::getNext()
{
		return next;
}
Uav::Node::~Node()
{

}