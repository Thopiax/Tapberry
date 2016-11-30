#include "util.h"

int get_next_sprite_num(void)
{
  for (int i = 0; i < MAX_NUM_OF_SPRITES; i++) {
    if (all_sprites[i] == NULL) {
      return i;
    }
  }
  return (-1);
}

int percent_x(int x)
{
  return x * (long) WINDOW_WIDTH / 100.0;
}

int percent_y(int y)
{
  return y * (WINDOW_HEIGHT / 100.0);
}

SDL_Surface *load_surface(const char *filename)
{
  // initialize local variables
  SDL_Surface *surface;
  // get the filename with its path
  surface = IMG_Load(filename);
  check_ptr(surface, "Couldn't load surface");
  surface = SDL_ConvertSurfaceFormat(surface, PIXEL_FORMAT, 0);

  check_sdl_int(SDL_SetColorKey(surface, SDL_TRUE,
                SDL_MapRGBA(surface->format, 0x0, 0x0, 0x0, 0xF)),
                "Unable to set color key to surface");
  SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
  // SDL_SetSurfaceAlphaMod(surface, 0);
  check_sdl_int(SDL_SetSurfaceRLE(surface, SDL_TRUE),
    "Unale to make the game foreground an RLE surface");
  // get the texture
  return surface;
}

SDL_Rect get_rect_from_surface(int x, int y, SDL_Surface *surface)
{
  SDL_Rect result;
  result.x = x;
  result.y = y;
  // get the width and height of the texture
  result.w = surface->w;
  result.h = surface->h;
  return result;
}

void start_game(void (*func)(sprite_t *sprite))
{
  if (gm_st == IN_MENU) {
    gm_st = IN_GAME;
    apply_to_all_sprites(func);
    background = all_surfaces[GAME_FOREGROUND_IND];
    button_press.left = 0;
    button_press.middle = 0;
    button_press.right = 0;
    button_press.end = 0;
  }
}

int is_start_col_free(col_pos_t col_pos)
{
  for (int i = 0; i < MAX_NUM_OF_SPRITES; i++) {
    if (all_sprites[i] != NULL && all_sprites[i]->col_pos == col_pos) {
      if (all_sprites[i]->rect.y < percent_x(START_LINE)) {
        return 0;
      }
    }
  }
  return 1;
}

void apply_to_all(void **list, void (*func)())
{
  for (int i = 0; i < MAX_NUM_OF_SPRITES; i++) {
    if (list[i] != NULL) {
      func(list[i]);
    }
  }
}

void apply_to_all_sprites(void (*func)(sprite_t *sprite))
{
  apply_to_all((void **) all_sprites, func);
}

void apply_to_all_surfaces(void (*func)(SDL_Surface *surface))
{
  apply_to_all((void **) all_surfaces, func);
}

void render_miss(void)
{
  SDL_Rect rect;
  rect = get_rect_from_surface(percent_x(92), percent_y(5), all_surfaces[CROSS_IND]);
  for (int i = 0; i < missed; i++) {
    SDL_UpdateTexture(screen_texture, &rect, all_surfaces[CROSS_IND]->pixels,
                      all_surfaces[CROSS_IND]->pitch);
    rect.y += rect.h + percent_y(1);
  }
}

col_pos_t get_rand_pos(void)
{
  // set defaults already no need for them later
  col_pos_t col_pos;
  // set a random x position
  int rand_pos = rand() % 3;
  switch (rand_pos) {
    case 0: col_pos = LEFT_COL; break;
    case 1: col_pos = MIDDLE_COL; break;
    default: col_pos = RIGHT_COL;
  }
  return col_pos;
}

SDL_Surface *get_rand_sprite(void)
{
  SDL_Surface *surface;
  int rand_text = rand() % 3;
  switch (rand_text) {
    case 0:  surface = all_surfaces[BLKBRY_IND]; break;
    case 1:  surface = all_surfaces[BLUBRY_IND]; break;
    default: surface = all_surfaces[RSPBRY_IND]; break;
  }
  return surface;
}
