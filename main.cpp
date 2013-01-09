#include "main.h"

using namespace std;

int main(int argc, char* args[])
{
	SDL_Surface *screen;
	int menu_option = -1;
	
	screen = scrns::MainMenu();
	
	while(menu_option == -1)
	{  
		menu_option = scrns::MainMenu_survey();
		
		if(menu_option == 1)
		{ 
			cout << "Starting new game..." << endl;
		}
	}
	
	SDL_FreeSurface(screen);
	return 0;
}
