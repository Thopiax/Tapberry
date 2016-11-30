/* MAIN HEADER FILE */
#ifndef MAIN_H
#define MAIN_H

/* IMPORTS */
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <wiringPi.h>

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 460
#define CIRCLE_WIDTH 90
#define CIRCLE_HEIGHT 63
#define BITS_PER_PIXEL 32

/* FUNCTION DECLARATIONS */
void init(void);
void anime(void);
void input_handle(void);
void press_left(void);
void press_middle(void);
void press_right(void);
void clean_up(void);
void load_images(void);
void init_coordinates(void);
/* END HEADER FILE FOR MAIN */
#endif
