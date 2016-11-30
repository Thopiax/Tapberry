#include "error.h"

// STATIC FUNCTIONS
static void thr_error(const char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

void check_ptr(void *ptr, char *msg)
{
  if (ptr == NULL) {
    thr_error(msg);
  }
}

void check_sdl_int(int num, const char *msg)
{
  if (num != 0) {
    thr_error(msg);
  }
}

void *careful_malloc(int size)
{
  void *result = malloc(size);
  check_ptr(result, "Unable to allocate memory");
  return result;
}

void *careful_calloc(int nitems, int size)
{
  void *result = calloc(nitems, size);
  check_ptr(result, "Unable to allocate memory");
  return result;
}
