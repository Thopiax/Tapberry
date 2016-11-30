#ifndef STATE_H
#define STATE_H

#include "config.h"
#include "error.h"
#include "util.h"
#include "image.h"
#include "sprite.h"

void state_init(void);
void state_destroy(void);
void state_render(void);
void check_status(int frame_counter);
void menu_init(void);
#endif
