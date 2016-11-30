CC      = gcc

UNAME   = $(shell uname)
ifeq ($(UNAME), Darwin)
CFLAGS  = -Wall -g -DEFAULT_SOURCE -std=c99 -Werror -pedantic
LDFLAGS = -I/Library/Frameworks/SDL2.framework/Headers -framework SDL2 -I/Library/Frameworks/SDL2_image.framework/Headers -framework SDL2_image -I/Library/Framworks/SDL2_ttf.framework/Headers -framework SDL2_ttf
else
CFLAGS  = -Wall -g -DEFAULT_SOURCE -std=c99 -lwiringPi -lSDL2 -lSDL2_image -lSDL2_ttf -Werror -pedantic
LDFLAGS = $(shell pkg-config --cflags --libs sdl2)
endif

OBJ = main.o error.o util.o state.o sprite.o image.o text.o
DEPS = config.h main.h error.h util.h state.h sprite.h image.h text.h

.SUFFIXES: .c .o

.PHONY: all clean

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.c $(DEPS) $(LDFLAGS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(wildcard *.o)
	rm -f main
