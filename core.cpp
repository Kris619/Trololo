#include "main.h"

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
	
	void apply_image(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = 0)
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
	// Returns 1 (true) on success, 0 (false) on error.
	bool initiateSDL(SDL_Surface *screen, int x, int y)
	{
		SDL_Surface *vid_init;
		int init, ttf_ret;
	
		// Initiate SDL and check
		init = SDL_Init(SDL_INIT_VIDEO);
		if(init < 0)
		{
			fprintf(stderr, "Unable to initiate SDL: %s\n", SDL_GetError());
		    return false;
		}

		
		// Set video and check
		vid_init = SDL_SetVideoMode(x, y, 32, SDL_SWSURFACE);
		if(vid_init == 0)
		{
		    fprintf(stderr, "Video initialization failed: %s", SDL_GetError());
		    return false;
		}


		// Get video surface and check
		screen = SDL_GetVideoSurface();
		if(screen == 0)
		{
		    fprintf(stderr, "Failed to get video surface: %s", SDL_GetError());
		    return false;
		}


		// Set window title
		SDL_WM_SetCaption(WINDOW_TITLE, 0);


		// Initialize SDL_ttf and check
		ttf_ret = TTF_Init();
		if(ttf_ret == -1)
		{
		    fprintf(stderr, "True Type Font initialization failed: %s", SDL_GetError());
		    return false;
		}

		// Success: return video surface
		return true;
	}

	SDL_Surface * MainMenu()
	{
		// Screen
		SDL_Surface *screen = 0;

		SDL_Surface *background = 0;
		SDL_Surface *characters = 0;
		SDL_Surface *message = 0;


		// Image filenames
		const char *background_image = "stage1.bmp";
		const char *characters_image = "characters.bmp";

		// Char
		SDL_Rect clip[2];

		initiateSDL(screen, 900, 675);

		if(screen == 0)
		{
			fprintf(stderr, "Start up failure.\n");
			return NULL;
		}
		else
		{
			// Load images
			background = scrnfunk::load_image(background_image);
			characters = scrnfunk::load_image(characters_image);
		
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
			scrnfunk::RemoveColor(characters, 0x00, 0xFF, 0x00); // Green
		
			// Blit background image
			scrnfunk::apply_image(0, 0, background, screen);
		
			// Blit troll image
			scrnfunk::apply_image(700, 40, characters, screen, &clip[0]);
		
			// Blit codfish image
			scrnfunk::apply_image(150, 300, characters, screen, &clip[1]);

			// Setup welcome text
			SDL_Color whitecolor = { 255, 255, 255 };
			TTF_Font *font = TTF_OpenFont("CaviarDreams.ttf", 80);
			const char* text = "Welcome to Trololo";
		
		
			if(!font)
			{
				fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
			}
		
			/*
					Checks if font or text is 0 due to the documentation:
					0 font into this function will cause a segfault.
					0 text into this function will result in undefined behavior.
			*/
			if(font != 0 && text != 0)
				message = TTF_RenderText_Solid(font, text, whitecolor);
			else
				fprintf(stderr, "TFF Render Text Solid Error: init error\n");
		
			// Apply message
			if(message != 0)
				scrnfunk::apply_image(100, 200, message, screen);
			else
				fprintf(stderr, "TFF Render Text Solid Error: apply error\n");
		
			if(screen != 0)
				SDL_Flip(screen);
			else
				fprintf(stderr, "Couldn't update screen.\n");
		}
	
		return screen;
	}
}

