#pragma once
#ifndef PERIMETER_H
#define PERIMETER_H true

#include "node.h"
#include "canvas.h"
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

	private:
		Node *head;
		Node *tail;
		Canvas* canvas;
	};


}

#endif