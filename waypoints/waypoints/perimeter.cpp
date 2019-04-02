#include "perimeter.h"
#include "tkmath.h"
#include <iostream>


#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif
void Uav::Perimeter::addNode(int x, int y)
{
	Node *temp = new Node;
	temp->setLocation(x, y);
	temp->setNext(nullptr);
	if (head == nullptr) // this node, temp is the first node
	{
		head = temp;
		tail = temp;
		temp = nullptr;
	}
	else // set this node, temp, as the latest node
	{
		tail->setNext(temp);
		tail = temp;
		tail->setLocation(temp->getLocation());
	}

}

void Uav::Perimeter::addNode(Point p)
{
	addNode(p.getX(), p.getY());
}

void Uav::Perimeter::addWaypoint(int x, int y)
{
	Waypoint *temp = new Waypoint;
	temp->setLocation(x, y);
	temp->setNext(nullptr);
	if (start == nullptr) // this node, temp is the first node
	{
		start = temp;
		end = temp;
		temp = nullptr;
	}
	else // set this node, temp, as the latest node
	{
		end->setNext(temp);
		end = temp;
		end->setLocation(temp->getLocation());
	}
}

void Uav::Perimeter::addWaypoint(Point p)
{
	addWaypoint(p.getX(), p.getY());
}



Uav::Node* Uav::Perimeter::getNodeAt(int i)
{
	Node *temp = new Node;
	temp->setNext(head->getNext());
	int h = 0;
	for (int h = 0; h < i; h++)
	{
		if (temp->getNext() == nullptr)
		{
			return temp;
		}
			temp = temp->getNext();
			h++;	
	}
	return temp;
}



Uav::Perimeter::Perimeter()
{
	head = nullptr;
	tail = nullptr;
	closed = false;
	bounded = false;
}

void Uav::Perimeter::close()
{
	closed = true;
}

int Uav::Perimeter::length()
{
	Node *temp = new Node;
	temp->setLocation(head->getLocation());
	temp->setNext(head->getNext());
	int h = 0;
	while (temp != tail)
	{
		temp = temp->getNext();
		h++;
	}
	return h;
}

void Uav::Perimeter::createBounds()
{
	int l = length();
	bounds = new Vec2d[l+1];
	Node* origin = head;
	for (int i = 0; i < l; i++)
	{
		bounds[i].setOriginX(origin->getLocation().getX());
		bounds[i].setOriginY(origin->getLocation().getY());
		
		bounds[i].setX(origin->getNext()->getLocation().getX() - bounds[i].getOriginX());
		bounds[i].setY(origin->getNext()->getLocation().getY() - bounds[i].getOriginY());
		if (origin != tail)
		{
			origin = origin->getNext();
		}
	}
	bounds[l].setOriginX(tail->getLocation().getX());
	bounds[l].setOriginY(tail->getLocation().getY());
	bounds[l].setX(head->getLocation().getX() - tail->getLocation().getX());
	bounds[l].setY(head->getLocation().getY() - tail->getLocation().getY());
	bounded = true;
}

int Uav::Perimeter::maxX()
{
	int max = head->getLocation().getX();
	Node *temp = new Node;
	temp = head;
	while (temp != nullptr)
	{
		if (temp->getLocation().getX() > max)
			max = temp->getLocation().getX();
		temp = temp->getNext();
	}
	return max;
}

int Uav::Perimeter::maxY()
{
	int max = head->getLocation().getY();
	Node *temp = new Node;
	temp = head;
	while (temp != nullptr)
	{
		if (temp->getLocation().getY() > max)
			max = temp->getLocation().getY();
		temp = temp->getNext();
	}
	return max;
}

int Uav::Perimeter::minX()
{
	int min = head->getLocation().getX();
	Node *temp = new Node;
	temp = head;
	while (temp != nullptr)
	{
		if (temp->getLocation().getX() < min)
			min = temp->getLocation().getX();
		temp = temp->getNext();
	}
	return min;
}

int Uav::Perimeter::minY()
{
	int min = head->getLocation().getY();
	Node *temp = new Node;
	temp = head;
	while (temp != nullptr)
	{
		if (temp->getLocation().getY() < min)
			min = temp->getLocation().getY();
		temp = temp->getNext();
	}
	return min;
}

void Uav::Perimeter::createWaypoints()
{
	if (!closed)
		close();
	if (!bounded)
		showBounds();

	int l = length();
	Point* ref = new Point(0, 0);
	Point* prev = new Point(0, 0);
	Point* tp = new Point(0, 0);

	for (int index = 0; index <= l; index++) // for each bounding line
	{
		
		for (int i = minY()-5; i < maxY()+5; i += 15) // move through y levels
		{
			if ((i - bounds[index].getOriginY())*(i - (bounds[index].getOriginY() + bounds[index].getY())) < 0
				|| (i == bounds[index].getOriginY() + bounds[index].getY())
				|| (i == bounds[index].getOriginY())
					) // if bounds[index] crosses level i
			{
				for (int j = minX()-5; j <= maxX()+5; j++) // move through x values
				{
					tp->setX(j);
					tp->setY(i);
					ref->setY(i);

					if ( Tkmath::sameSideOfLine(*tp, *ref, bounds[index]) != Tkmath::sameSideOfLine(*prev, *ref, bounds[index]) && j != minX() - 5	// crossed a boundary
						|| (i == bounds[index].getOriginY() && j == bounds[index].getOriginX() )													// or j,i is a boundary origin
						|| (i == bounds[index].getOriginY() + bounds[index].getY() && j == bounds[index].getOriginX() + bounds[index].getX() ) )	// or j,i is a boundary destination
			
			
					prev->setX(tp->getX());
					prev->setY(tp->getY());
				}
			}
		}
	}
	
	delete tp;
	delete ref;
	delete prev;
}

void Uav::Perimeter::orderWaypoints()
{
	bool isSorted = false;
	//printWaypoints();
	Waypoint *temp = new Waypoint;
	do {
		isSorted = true;
		temp = start;
		while (temp != nullptr && temp->getNext() != nullptr)
		{
			
			if (temp->getNext()->getLocation().getY() < temp->getLocation().getY())
			{

				temp->swap();
				isSorted = false;
				
			}
			temp = temp->getNext();
		}
	} while (!isSorted);
	
	isSorted = false;
	do {
		isSorted = true;
		temp = start;
		while (temp != nullptr && temp->getNext() != nullptr && temp->getNext()->getNext() != nullptr)
		{
			if (temp->getLocation().getY() != temp->getNext()->getLocation().getY())
			{
				int diffToNext, diffToNextNext;
				diffToNext = temp->getNext()->getLocation().getX() - temp->getLocation().getX();
				diffToNextNext = temp->getNext()->getNext()->getLocation().getX() - temp->getLocation().getX();

				if (diffToNext*diffToNext > diffToNextNext*diffToNextNext)
				{
					temp->swapNexts();
					isSorted = false;
				}
				
			}
			temp = temp->getNext();
		}
	} while (!isSorted);
	printWaypoints();
}

void Uav::Perimeter::printWaypoints()
{

	Waypoint *temp = new Waypoint;
	temp = start;
	while (temp != nullptr)
	{
		int j = temp->getLocation().getX();
		int i = temp->getLocation().getY();
		std::cout << temp->getLocation().getX() << "," << temp->getLocation().getY() << std::endl;
		


		temp = temp->getNext();

	}
}
