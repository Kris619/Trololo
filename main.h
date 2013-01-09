#ifndef MAIN_H
#define MAIN_H

// SDL dependencies
#include "SDL/SDL.h" // SDL 1.2.15 (32 bit)
#include "SDL/SDL_image.h" // SDL_image (1.2.12)
#include "SDL/SDL_ttf.h" // SDL_tff (2.0.11)

// Standard dependencies
#include <iostream>
#include <cstdio>

namespace scrns
{
	SDL_Surface * initiateSDL(SDL_Surface *screen, int x, int y);
	SDL_Surface * MainMenu();
	int MainMenu_survey();
}

namespace scrnfunk
{
	SDL_Surface *load_image(const char *file);
	void apply_image(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = 0);
	bool RemoveColor(SDL_Surface* image, Uint8 R, Uint8 G, Uint8);
}

#define VERSION "0.1-alpha"
#define WINDOW_TITLE "Trololo"

#endif
