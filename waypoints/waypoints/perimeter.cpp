#include "perimeter.h"
#include "canvas.h"

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
		tail->setLocation(temp->getLocation().getX(), temp->getLocation().getY());
	}
}
void Uav::Perimeter::addNode(Point p)
{
	addNode(p.getX(), p.getY());
}
void Uav::Perimeter::deleteLastNode()
{

}
Uav::Node* Uav::Perimeter::getNodeAt(int i)
{
	Node *temp = new Node;
	temp = head;
	int h = 0;
	while (temp != nullptr || h < i)
	{
		*temp = *temp->getNext();
		h++;
	}
	return temp;
}

void Uav::Perimeter::showNodes()
{
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
		


		temp = temp->getNext();
	}
}

Uav::Perimeter::Perimeter(Canvas* c)
{
	canvas = c;
	head = nullptr;
	tail = nullptr;
}

Uav::Perimeter::~Perimeter()
{
}