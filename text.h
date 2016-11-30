#ifndef TEXT_H
#define TEXT_H

/* INCLUSIONS */
#include "config.h"
#include "util.h"
#include "error.h"

/* DECLARATIONS */
void init_text(void);
void render_text(char *message, int x, int y, SDL_Color color, int blended);
void text_quit(void);
#endif
