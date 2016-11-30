#ifndef IMAGE_H
#define IMAGE_H

#include "config.h"
#include "error.h"
#include "util.h"

void init_surfaces(void);
void init_texture(void);
void destroy_surface(SDL_Surface *surface);

#endif
