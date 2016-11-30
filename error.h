#ifndef ERROR_H
#define ERROR_H

/* INCLUSIONS */
#include "config.h"

/* DECLARATIONS */
// SDL RELATED
void check_ptr(void *ptr, char *msg);
void check_sdl_int(int num, const char *msg);
// OTHERS
void *careful_malloc(int size);
void *careful_calloc(int nitems, int size);

#endif
