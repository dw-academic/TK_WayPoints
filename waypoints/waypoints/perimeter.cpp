#include "perimeter.h"
#include "tkmath.h"
#include <iostream>


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
	showNodes();
}
void Uav::Perimeter::addNode(Point p)
{
	addNode(p.getX(), p.getY());
}
void Uav::Perimeter::deleteLastNode()
{
	showNodes();
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

void Uav::Perimeter::showNodes()
{
	SDL_SetRenderDrawColor(canvas->getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(canvas->getRenderer());
	Node *temp = new Node;
	temp = head;
	while (temp != nullptr)
	{
		SDL_SetRenderDrawColor(canvas->getRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawLine(canvas->getRenderer(),
			temp->getLocation().getX() - 4,
			temp->getLocation().getY() - 4,
			temp->getLocation().getX() + 4,
			temp->getLocation().getY() + 4);
		SDL_RenderDrawLine(canvas->getRenderer(),
			temp->getLocation().getX() - 4,
			temp->getLocation().getY() + 4,
			temp->getLocation().getX() + 4,
			temp->getLocation().getY() - 4);

#ifdef DRAWLINES
		if (tail != head && temp->getNext() != nullptr)
		{
			SDL_SetRenderDrawColor(canvas->getRenderer(), 0, 0, 255, 255);
			SDL_RenderDrawLine(canvas->getRenderer(),
				temp->getLocation().getX(),
				temp->getLocation().getY(),
				temp->getNext()->getLocation().getX(),
				temp->getNext()->getLocation().getY());
			if (closed)
			{
				SDL_SetRenderDrawColor(canvas->getRenderer(), 0, 0, 255, 255);
				SDL_RenderDrawLine(canvas->getRenderer(),
					tail->getLocation().getX(),
					tail->getLocation().getY(),
					head->getLocation().getX(),
					head->getLocation().getY());
			}
		}
#endif
		temp = temp->getNext();
	}
}

void Uav::Perimeter::showBounds()
{
	int l = length();
	SDL_SetRenderDrawColor(canvas->getRenderer(), 0, 255, 0, 255);
	createBounds();
	for (int i = 0; i <= l; i++)
	{
		SDL_RenderDrawLine(canvas->getRenderer(),
			bounds[i].getOriginX(),
			bounds[i].getOriginY(),
			bounds[i].getOriginX() + bounds[i].getX(),
			bounds[i].getOriginY() + bounds[i].getY()
		);
	}

}


Uav::Perimeter::Perimeter(Canvas* c)
{
	canvas = c;
	head = nullptr;
	tail = nullptr;
	closed = false;
}

void Uav::Perimeter::close()
{
	closed = true;
	showNodes();
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
	// TODO: Completely rework the way of making bounds
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
}

void Uav::Perimeter::fill()
{
	SDL_SetRenderDrawColor(canvas->getRenderer(), 255, 0, 255, 255);
	for(int i = minY(); i < maxY(); i += 5)
	{
		SDL_RenderDrawLine(canvas->getRenderer(),
			minX(), i, maxX(), i);
	}
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
	SDL_SetRenderDrawColor(canvas->getRenderer(), 255, 128, 255, 255);


	int l = length();
	Point* ref = new Point(0, 0);
	Point* prev = new Point(0, 0);
	Point* tp = new Point(0, 0);

	for (int index = 0; index < l; index++) // for each bounding line
	{
		
		for (int i = minY()-5; i < maxY()+5; i += 5) // move through y levels
		{
			if ((i - bounds[index].getOriginY())*(i - (bounds[index].getOriginY() + bounds[index].getY())) < 0) // if bounds[index] crosses level i
			{
				for (int j = minX()-5; j <= maxX()+5; j++) // move through x values
				{
					tp->setX(j);
					tp->setY(i);
					ref->setY(i);

					if (Tkmath::sameSideOfLine(*tp, *ref, bounds[index]) != Tkmath::sameSideOfLine(*prev, *ref, bounds[index]) && j != minX()-5)
					{
						for (int r = -1; r <= 1; r++)
						{
							SDL_RenderDrawPoint(canvas->getRenderer(), j + r, i + r);
							SDL_RenderDrawPoint(canvas->getRenderer(), j + r, i - r);
							SDL_RenderDrawPoint(canvas->getRenderer(), j, i + r);
							SDL_RenderDrawPoint(canvas->getRenderer(), j + r, i);
						}
					}

					prev->setX(tp->getX());
					prev->setY(tp->getY());
				}
			}
		}
	}
}
Uav::Perimeter::~Perimeter()
{
}