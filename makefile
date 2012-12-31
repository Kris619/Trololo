SDL_LIBS=`pkg-config --libs sdl` -lSDL -lSDL_image -lSDL_ttf
INCLUDES=-I/opt/local/include
all:
	g++ -Wall -g main.cpp core.cpp main.h -o Trololo ${INCLUDES} ${SDL_LIBS}
