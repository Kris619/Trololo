#include "main.h"

using namespace std;

int main(int argc, char* args[])
{
	SDL_Surface *screen;
	
	// Display main menu
	screen = scrns::MainMenu();
	
	// Main menu keyboard surveying
	screen = scrns::MainMenu_survey(screen);
	
	SDL_FreeSurface(screen);
	return 0;
}
