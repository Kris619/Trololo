ifdef SystemRoot
	INCLUDES=-IC:\MinGW\include
	SDL_LIBS=-lmingw32 -lSDLmain -lSDL -mwindows -lSDL_image -lSDL_ttf
else
	INCLUDES=-I/opt/local/include
	SDL_LIBS=`pkg-config --libs sdl` -lSDL -lSDL_image -lSDL_ttf
endif

all:
	g++ -Wall main.cpp core.cpp main.h -o mario ${INCLUDES} ${SDL_LIBS}
