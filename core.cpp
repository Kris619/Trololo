#include "main.h"

using namespace std;

namespace scrnfunk
{
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

		if(image_format != 0)
		{
		    // Optimize
		    screen_format = SDL_DisplayFormat(image_format);
		
		    // Release old image
		    SDL_FreeSurface(image_format);
		}

		return screen_format;
	}
	
	void apply_image(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
	{
		SDL_Rect pos;

		pos.x = x;
		pos.y = y;

		SDL_BlitSurface(source, clip, destination, &pos);
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
}


namespace scrns
{
	// Returns a pointer on success, NULL on an error
	SDL_Surface *initiateSDL(int x, int y)
	{
		SDL_Surface *screen = NULL;
		SDL_Surface *vid_init;
		int init;//, ttf_ret;
	
		// Initiate SDL and check
		init = SDL_Init(SDL_INIT_VIDEO);
		if(init < 0)
		{
			fprintf(stderr, "Unable to initiate SDL: %s\n", SDL_GetError());
			return NULL;
		}

		
		// Set video and check
		vid_init = SDL_SetVideoMode(x, y, 32, SDL_SWSURFACE);
		if(vid_init == 0)
		{
		    fprintf(stderr, "Video initialization failed: %s", SDL_GetError());
		    return NULL;
		}


		// Get video surface and check
		screen = SDL_GetVideoSurface();
		if(screen == NULL)
		{
		    fprintf(stderr, "Failed to get video surface: %s", SDL_GetError());
		    return NULL;
		}

		// Set window title
		SDL_WM_SetCaption(WINDOW_TITLE " " VERSION, 0);

		/*
		// Initialize SDL_ttf and check
		ttf_ret = TTF_Init();
		if(ttf_ret == -1)
		{
		    fprintf(stderr, "True Type Font initialization failed: %s", SDL_GetError());
		    return NULL;
		}
		*/
		
		SDL_FreeSurface(vid_init);

		// Success
		return screen;
	}

	/*SDL_Surface *MainMenu()
	{
		
	}*/
	
	SDL_Surface *Stage1()
	{
		// Screen
		SDL_Surface *screen = NULL;
		SDL_Surface *background = NULL;

		// Image filenames
		const char *background_image = "bin/stage.bmp";
		
		screen = initiateSDL(900, 646);

		if(screen == NULL)
		{
			fprintf(stderr, "Start up failure.\n");
			return NULL;
		}
		else
		{
			// Load images
			background = scrnfunk::load_image(background_image);

			// Blit background image
			scrnfunk::apply_image(0, 0, background, screen);

			// Update screen with all applied images
			if(screen != 0)
				SDL_Flip(screen);
			else
				fprintf(stderr, "Couldn't update screen.\n");
		}
					
		// Free old surfaces
		SDL_FreeSurface(background);
		SDL_FreeSurface(screen);

		return screen;
	}
	
	SDL_Surface *Movement(SDL_Surface *screen)
	{
		// Movement
		// D -- Mario move LEFT
		// A -- Mario move RIGHT

		SDL_Surface *background = NULL;
		SDL_Surface *mario0 = NULL;
		//SDL_Surface *mario1 = NULL;
		//SDL_Surface *mario2 = NULL;
		SDL_Surface *mario3 = NULL;
		//SDL_Surface *mario4 = NULL;
		//SDL_Surface *mario5 = NULL;
		
		int x,y;
		x = 125;
		y = 520;

		// Image filenames
		const char *background_image = "bin/stage.bmp";
		const char *mario_image0 = "bin/IMG0.bmp";
		//const char *mario_image1 = "bin/IMG1.bmp";
		//const char *mario_image2 = "bin/IMG2.bmp";
		const char *mario_image3 = "bin/IMG3.bmp";
		//const char *mario_image4 = "bin/IMG4.bmp";
		//const char *mario_image5 = "bin/IMG5.bmp";

		background = scrnfunk::load_image(background_image);
		mario0 = scrnfunk::load_image(mario_image0);
		//mario1 = scrnfunk::load_image(mario_image1);
		//mario2 = scrnfunk::load_image(mario_image2);
		mario3 = scrnfunk::load_image(mario_image3);
		//mario4 = scrnfunk::load_image(mario_image4);
		//mario5 = scrnfunk::load_image(mario_image5);
		
		SDL_Rect clip;

		clip.x = x;
		clip.y = y;
		clip.w = 100;
		clip.h = 100;

		scrnfunk::RemoveColor(mario0, 0x00, 0x00, 0xFF); // Blue
		//scrnfunk::RemoveColor(mario1, 0x00, 0x00, 0xFF); // Blue
		//scrnfunk::RemoveColor(mario2, 0x00, 0x00, 0xFF); // Blue
		scrnfunk::RemoveColor(mario3, 0x00, 0x00, 0xFF); // Blue
		scrnfunk::apply_image(x, y, mario0, screen);
					
		if(screen != 0)
			SDL_Flip(screen);

		SDL_Event event;
		
		while(1)
		{
			while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT)
					return NULL;

				else if(event.type == SDL_KEYDOWN)
				{
					if(event.key.keysym.sym == SDLK_d) // RIGHT
					{	
						scrnfunk::apply_image(x, y, background, screen, &clip); // Cover current Mario
						x=x+10;
						clip.x = x;
						scrnfunk::apply_image(x, y, mario3, screen); // Place new Mario
					}
					else if(event.key.keysym.sym == SDLK_a) // LEFT
					{
						scrnfunk::apply_image(x, y, background, screen, &clip); // Cover current Mario
						x=x-10;
						clip.x = x;
						scrnfunk::apply_image(x, y, mario3, screen); // Place new Mario
					}
				}
			}
			
			if(screen != 0)
				SDL_Flip(screen);
			else
				fprintf(stderr, "Couldn't update screen.\n");
		}
			
		return screen;
	}
}
