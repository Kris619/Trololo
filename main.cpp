#include "main.h"

using namespace std;

int main(int argc, char* args[])
{
	SDL_Surface *screen;
	
	// Display main menu
	screen = scrns::MainMenu();
	
	// Main menu option return
	int menu_option;
	
	menu_option = scrns::MainMenu_survey();
	
	switch(menu_option)
	{
		case 1:
			// User wants to start a new game
			cout << "Starting new game..." << endl;
			break;
		case 2:
			// User wants to exit the game
			break;
		default:
			cout << "Fatal Error: Main Menu option given was unknown." << endl;
		
	}
	
	SDL_FreeSurface(screen);
	return 0;
}
