#pragma once
#ifndef NODE_H
#define NODE_H true
#include "point.h"

namespace Uav
{
	class Node
	{
	public:
		Node();
		Node(int x, int y);
		Node(Point);
		~Node();
		Point getLocation();
		void setNext(Node*);
		Node* getNext();
		
		void setLocation(int x, int y);
	private:
		Point location;
		Node *next;
	};

}

#endif