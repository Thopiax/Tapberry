#ifndef UTIL_H
#define UTIL_H

#include "config.h"
#include "error.h"

// state handling
int get_next_sprite_num(void);
int percent_x(int x);
int percent_y(int y);
// sdl handling
SDL_Surface *load_surface(const char *filename);
SDL_Rect get_rect_from_surface(int x, int y, SDL_Surface *surface);
void        start_game(void (*func)(sprite_t *sprite));
void        init_background(void);
int         is_start_col_free(col_pos_t col_pos);
// sprite handling
void apply_to_all(void **list, void (*func)());
void apply_to_all_sprites(void (*func)(sprite_t *sprite));
void apply_to_all_surfaces(void (*func)(SDL_Surface *surface));
void render_miss(void);
col_pos_t get_rand_pos(void);
SDL_Surface *get_rand_sprite(void);

#endif
