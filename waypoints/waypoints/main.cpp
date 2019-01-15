#include "canvas.h"
#include "perimeter.h"
#include <iostream>
extern bool TK_QUIT = false;

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING); // initialize all SDL layers
	SDL_Renderer* r = NULL;
	SDL_Surface* s = NULL;
	SDL_Window* w = NULL;
	SDL_Event e;
	Uav::Canvas *canvas = new Uav::Canvas(r, s, w, &e);
	SDL_SetRenderDrawColor(canvas->getRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(canvas->getRenderer());

	int response = 0;
	printf("\n= Ready = \n");
	SDL_RestoreWindow(canvas->getWindow());
	SDL_RenderClear(canvas->getRenderer());
	Uav::Perimeter *perimeter = new Uav::Perimeter(canvas);
	

	while (!TK_QUIT)
	{
		response = canvas->GetAllEvents();


		if (response == TK_CODE_QUITTING)
		{
			TK_QUIT = true;
		}
		else if (response == TK_CODE_SAVE)
		{
			canvas->SaveImage();
		}
		else if (response == TK_CODE_GENERATE)
		{
			perimeter->showBounds();
			canvas->UpdateToScreen();
		}
		else if (response == TK_CODE_LEFTCLICK)
		{
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			perimeter->addNode(mx, my); // add point at mouse location
			canvas->UpdateToScreen();
		}
		else if (response == TK_CODE_RIGHTCLICK)
		{
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			perimeter->close();
			canvas->UpdateToScreen();
		}
		else if (response == TK_CODE_FILL)
		{
			
			perimeter->fill();
			canvas->UpdateToScreen();
		}
		else if (response == TK_CODE_NAVIGATE)
		{

			perimeter->createWaypoints();
			canvas->UpdateToScreen();
		}
	}

	if (TK_QUIT)
	{
		SDL_Delay(500);
		SDL_Quit();
	}



	return 0;
}