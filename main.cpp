#include "main.h"

int main(int argc, char* args[])
{					
	SDL_Event event;
	int quit = 1;

	SDL_Surface *screen;
	
	screen = scrns::MainMenu();

	if(screen == NULL)
		return 1;
	  
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

