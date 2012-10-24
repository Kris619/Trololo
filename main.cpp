// SDL + Extensions
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

// Common SDL functions for general processing.
#include "commonSDL.h"

#define WINDOW_TITLE "Trololo"

// Screen
SDL_Surface *screen = NULL;

// Images
SDL_Surface *background = NULL;
SDL_Surface *troll = NULL;

// Image filenames
const char *background_image = "whitehouse.bmp";
const char *troll_image = "troll.bmp";


int main(int argc, char* args[])
{					
	screen = StartUp(WINDOW_TITLE,678,678);

	if(screen == NULL)
	{
		fprintf(stderr, "Start up failure.\n");
		return 1;
	}
	else
	{
		// Load images
		background = load_image(background_image);
		troll = load_image(troll_image);
		
		// Remove the background (green) of the troll
		RemoveColor(troll, 0x00,0xFF,0x00);
		
		// Blit
		apply_image(0, 0, background, screen);
		apply_image(0, 0, troll, screen);
		
		if(screen != NULL)
			SDL_Flip(screen);
		else
			fprintf(stderr, "Couldn't update screen.\n");
		
		SDL_Event event;
		int quit = 1;
		
		// Check if user quit
		while(quit == 1)
		{
			while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT)
					quit = 0;
			}
		}

		return 0;
	}
}

