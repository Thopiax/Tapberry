#ifndef SPRITE_H
#define SPRITE_H

/* INCLUSIONS */
#include "config.h"
#include "error.h"
#include "util.h"

/* DECLARATIONS */
void sprite_init(col_pos_t col_pos, SDL_Surface *surface);
void sprite_init_rand(SDL_Surface *surface);
int is_sprite_init(sprite_t *sprite);
void destroy_sprite(sprite_t *sprite);
void update_sprite_pos(sprite_t *sprite);
void render_sprite(sprite_t *sprite);
void add_to_render_sprite(sprite_t *sprite);
void remove_to_render_sprite(sprite_t *sprite);
void miss_sprite(void);
int  is_sprite_in_range(sprite_t *sprite, int y1, int y2);

#endif
