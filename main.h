/* MAIN HEADER FILE */
#ifndef MAIN_H
#define MAIN_H

/* IMPORTS */
#include "config.h"
#include "error.h"
#include "util.h"
#include "text.h"
#include "state.h"
#include "sprite.h"
#include "image.h"
#include <wiringPi.h>

/* FUNCTION DECLARATIONS */
void setup_buttons();
void init_sprites(void);
void anime(void);
void make_new_line(void);
void game_render(void);
void input_handle(void);
void check_hit(col_pos_t col_pos);
void clean_up(void);
void init_coordinates(void);

/* MACROS */
#define BUTTON_L 0
#define BUTTON_M 1
#define BUTTON_R 2
#define BUTTON_E 3

/* END HEADER FILE FOR MAIN */
#endif
