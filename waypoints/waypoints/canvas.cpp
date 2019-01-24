#include "canvas.h"
#include <time.h>
#include <iostream>
#include <sstream>

Uav::Canvas::Canvas(SDL_Renderer* r, SDL_Surface* s, SDL_Window* w, SDL_Event* e)
{
	w = SDL_CreateWindow("Waypoint Algorithm Testing", // create our window object reference by pointer
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		TK_WINDOW_WIDTH, TK_WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);
	std::cout << SDL_GetError() << std::endl;
	SDL_MinimizeWindow(w);
	r = SDL_CreateRenderer(w, -1, 0);
	renderer = r;
	surface = s;
	window = w;
	events = e;
	SDL_BlitSurface(surface, NULL, surface, NULL);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

}

bool Uav::Canvas::SaveImage()
{
	time_t timer = time(NULL);
	std::stringstream oss;
	SDL_Window* SDLWindow = window;
	SDL_Renderer* SDLRenderer = renderer;
	std::string filepath = "..\\..\\screenshot-";
	std::string extension = ".bmp";
	oss << filepath << timer << extension;
	oss >> filepath;
	// copied from stackoverflow, be careful
	SDL_Surface* saveSurface = NULL;
	SDL_Surface* infoSurface = NULL;
	infoSurface = SDL_GetWindowSurface(SDLWindow);
	if (infoSurface == NULL) {
		std::cout << "Failed to create info surface from window in saveScreenshotBMP(string), SDL_GetError() - " << SDL_GetError() << "\n";
	}
	else {
		unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
		if (pixels == 0) {
			std::cout << "Unable to allocate memory for screenshot pixel data buffer!\n";
			return false;
		}
		else {
			if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0) {
				std::cout << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
				pixels = NULL;
				return false;
			}
			else {
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
				if (saveSurface == NULL) {
					std::cout << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
					return false;
				}
				SDL_SaveBMP(saveSurface, filepath.c_str());
				SDL_FreeSurface(saveSurface);
				saveSurface = NULL;
			}
			delete[] pixels;
		}
		SDL_FreeSurface(infoSurface);
		infoSurface = NULL;
	}
	std::cout << "File saved as " << filepath << "\n";
	return true;
}

void Uav::Canvas::UpdateToScreen()
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

int Uav::Canvas::GetAllEvents()
{
	while (SDL_PollEvent(events) != 0)
	{
		if (events->key.keysym.scancode == SDL_SCANCODE_Q && events->key.state == SDL_PRESSED)
		{
			return TK_CODE_QUITTING;
		}
		if (events->key.keysym.scancode == SDL_SCANCODE_F5 && events->key.state == SDL_PRESSED)
		{
			return TK_CODE_SAVE;
		}

		if (events->key.keysym.scancode == SDL_SCANCODE_G && events->key.state == SDL_PRESSED)
		{
			return TK_CODE_GENERATE;
		}
		if (events->key.keysym.scancode == SDL_SCANCODE_F && events->key.state == SDL_PRESSED)
		{
			return TK_CODE_FILL;
		}
		if (events->key.keysym.scancode == SDL_SCANCODE_W && events->key.state == SDL_PRESSED)
		{
			return TK_CODE_NAVIGATE;
		}
		if (events->button.type == SDL_MOUSEBUTTONUP && events->button.clicks == 1 && events->button.button == SDL_BUTTON_LEFT)
		{
			return TK_CODE_LEFTCLICK;
		}
		if (events->button.type == SDL_MOUSEBUTTONUP && events->button.clicks == 1 && events->button.button == SDL_BUTTON_RIGHT)
		{
			return TK_CODE_RIGHTCLICK;
		}

		if (events->key.keysym.scancode >= SDL_SCANCODE_A && events->key.keysym.scancode <= SDL_SCANCODE_0 && events->key.keysym.scancode != SDL_SCANCODE_Q && events->key.state == SDL_PRESSED)
		{
			return events->key.keysym.scancode;
		}

	}
	return 0;
}

SDL_Renderer* Uav::Canvas::getRenderer()
{
	return renderer;
}

SDL_Texture* Uav::Canvas::getTexture()
{
	return texture;
}

SDL_Window* Uav::Canvas::getWindow()
{
	return window;
}
