// SDL + Extensions
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

// Common SDL functions for general processing.
#include "commonSDL.h"

#define WINDOW_TITLE "Trololo"

// Screen
SDL_Surface *screen = NULL;

SDL_Surface *background = NULL;
SDL_Surface *characters = NULL;

SDL_Surface *message = NULL;

// Image filenames
const char *background_image = "stage1.bmp";
const char *characters_image = "characters.bmp";

// Char
SDL_Rect clip[2];


int main(int argc, char* args[])
{					
	screen = StartUp(WINDOW_TITLE, 900, 675);

	if(screen == NULL)
	{
		fprintf(stderr, "Start up failure.\n");
		return 1;
	}
	else
	{
		// Load images
		background = load_image(background_image);
		characters = load_image(characters_image);
		
		// The troll's coordinates 
		clip[0].x = 0;
		clip[0].y = 0;
		clip[0].w = 200;
		clip[0].h = 160;
		
		// The codfish's coordinates
		clip[1].x = 0;
		clip[1].y = 160;
		clip[1].w = 200;
		clip[1].h = 100;
		
		// Remove the background from the characters
		RemoveColor(characters, 0x00, 0xFF, 0x00); // Green
		
		// Blit background image
		apply_image(0, 0, background, screen);
		
		// Blit troll image
		apply_image(700, 40, characters, screen, &clip[0]);
		
		// Blit codfish image
		apply_image(150, 300, characters, screen, &clip[1]);

		// Setup welcome text
		SDL_Color whitecolor = { 255, 255, 255 };
		TTF_Font *font = TTF_OpenFont("CaviarDreams.ttf", 80);
		const char* text = "Welcome to Trololo";
		
		
		if(!font)
		{
			fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
		}
		
		/*
			Checks if font or text is NULL due to the documentation:
				NULL font into this function will cause a segfault.
				NULL text into this function will result in undefined behavior.
		*/
		if(font != NULL && text != NULL)
			message = TTF_RenderText_Solid(font, text, whitecolor);
		else
			fprintf(stderr, "TFF Render Text Solid Error: init error\n");
		
		// Apply message
		if(message != NULL)
			apply_image(100, 200, message, screen);
		else
			fprintf(stderr, "TFF Render Text Solid Error: apply error\n");
		
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

