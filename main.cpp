#include "main.h"

using namespace std;

int main(int argc, char* args[])
{
	SDL_Surface *screen;
	
	// Display main menu
	screen = scrns::Stage1();
	
	// Main menu keyboard surveying
	screen = scrns::Movement(screen);
	
	SDL_FreeSurface(screen);
	return 0;
}
