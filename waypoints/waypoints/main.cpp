#include "perimeter.h"
#include <iostream>
extern bool TK_QUIT = false;

int main()
{


	while (!TK_QUIT)
	{
		while (reading_file)
		{
			// TODO : fully implement this
			mx << file;
			my << file;
			perimeter->addNode(mx, my);
		}
		perimeter->close();
		perimeter->createWaypoints();
		perimeter->orderWaypoints();
		canvas->UpdateToScreen();
	}
	return 0;
}
