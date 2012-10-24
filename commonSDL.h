// SDL + Extensions
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// Standard
#include <cstdio>

SDL_Surface *StartUp(const char *title, int x, int y)
{
	SDL_Surface *screen;
	SDL_Surface *vid_init;
	int init;
	
	init = SDL_Init(SDL_INIT_VIDEO);
	
	// SDL failed to initiate
	if(init < 0)
	{
		fprintf(stderr, "Unable to initiate SDL: %s\n", SDL_GetError());
		return NULL;
	}
	
	vid_init = SDL_SetVideoMode(x, y, 32, SDL_SWSURFACE);
				
	// Video failed to be set
	if(vid_init == NULL)
	{
		fprintf(stderr, "Video initialization failed: %s", SDL_GetError());
		return NULL;
	}
								
	screen = SDL_GetVideoSurface();
	
	if(screen == NULL)
	{
		fprintf(stderr, "Failed to get video surface: %s", SDL_GetError());
		return NULL;
	}
	
	SDL_WM_SetCaption(title, NULL );
	
	// Success: return video surface
	return screen;
}

// Optimize image on load to reduce processing.
SDL_Surface *load_image(const char *file)
{
	SDL_Surface *image_format;
	SDL_Surface *screen_format;
	
	// Load image
	image_format = IMG_Load(file);
	
	/*
		DOES THE FILE EVEN EXIST?
	*/
	
	if(image_format != NULL)
	{
		// Optimize
		screen_format = SDL_DisplayFormat(image_format);
		
		// Release old image
		SDL_FreeSurface(image_format);
	}
	
	return screen_format;
}

void apply_image(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect pos;
	
	pos.x = x;
	pos.y = y;
	
	SDL_BlitSurface(source, NULL, destination, &pos);
}

// Removes color from an image.
bool RemoveColor(SDL_Surface* image, Uint8 R, Uint8 G, Uint8 B)
{
	int result;
	
	// Map color on the image
	Uint32 color = SDL_MapRGB(image->format, R, G, B);
	
	// Remove color from the image.
	result = SDL_SetColorKey(image, SDL_SRCCOLORKEY, color);
	
	if(!result)
		return true;
	else 
		return false;
}