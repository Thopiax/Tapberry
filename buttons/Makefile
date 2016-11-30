CC = gcc
CFLAGS = -g -std=c99 -lwiringPi 

readIn: readIn.c
	$(CC) $(CFLAGS) `sdl-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -o readIn readIn.c

music: music.c
	$(CC) $(CFLAGS) `sdl-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -o music music.c

clean:
	rm *.o
