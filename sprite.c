#include "sprite.h"

void sprite_init(col_pos_t col_pos, SDL_Surface *surface)
{
  // get next available index of sprites
  int sprite_num = get_next_sprite_num();
  // if there is one
  if (sprite_num >= 0) {
    // initialize the sprite
    sprite_t *sprite = careful_malloc(sizeof(sprite_t));
    // save it to the list
    all_sprites[sprite_num] = sprite;
    // store its id
    sprite->id = sprite_num;
    // store x value as the enum
    sprite->col_pos = col_pos;
    // don't render the sprite at first
    sprite->to_render = 1;
    sprite->hit = 0;
    // set its texture
    sprite->surface = surface;
    // make the rect
    sprite->rect = get_rect_from_surface(percent_x((int) col_pos),
                        DEFAULT_SCREEN_TOP,
                        sprite->surface);
    // move the sprite up beyond the screen
    sprite->rect.y -= sprite->rect.h;
    // and return the sprite
  } else {
    fprintf(stderr, "%s", "The sprite array is full!\n");
  }
}

void sprite_init_rand(SDL_Surface *surface)
{
  // initialize variables
  col_pos_t col_pos = get_rand_pos();
  if (is_start_col_free(col_pos)) {
    // set random berry value
    if (surface == NULL) {
      surface = get_rand_sprite();
    }
    // initialize it
    sprite_init(col_pos, surface);
  }
}

int is_sprite_init(sprite_t *sprite)
{
  return sprite->surface != NULL;
}

void destroy_sprite(sprite_t *sprite)
{
  // remove it from the sprite array
  all_sprites[sprite->id] = NULL;
  free(sprite);
}

void update_sprite_pos(sprite_t *sprite)
{
  // if the sprite is out of the window
  // then the player missed it
  if (sprite->rect.y > WINDOW_HEIGHT) {
    if (!sprite->hit) {
      // so add to miss
      miss_sprite();
    }
    // kill it
    destroy_sprite(sprite);
  } else {
    // otherwise make it go down
    sprite->rect.y += GRAVITY;
  }
}

void render_sprite(sprite_t *sprite)
{
  if (sprite->to_render) {
    // void *mPixels = NULL;
    // int mPitch;
    //
    // SDL_LockTexture(screen_texture, &sprite->rect, &mPixels, &mPitch);
    // SDL_LockSurface(sprite->surface);
    //
    // Uint16 *upixels = (Uint16 *) mPixels;
    // Uint16 transparent = SDL_MapRGBA(background->format, 0, 0, 0, 0xF);
    //
    // for (int i = 0; i < sprite->rect.h * sprite->rect.w; i++)
    //   {
    //       if (upixels[i] == transparent)
    //         upixels[i] = ((Uint32 *) background->pixels)[i];
    //   }
    //
    // // memcpy( mPixels, sprite->surface->pixels, sprite->surface->pitch * sprite->surface->w);
    //
    // SDL_UnlockSurface(sprite->surface);
    // SDL_UnlockTexture(screen_texture);
    SDL_UpdateTexture(screen_texture, &sprite->rect, sprite->surface->pixels,
                      sprite->surface->pitch);
  }
}

void add_to_render_sprite(sprite_t *sprite)
{
  sprite->to_render = 1;
}

void remove_to_render_sprite(sprite_t *sprite)
{
  sprite->to_render = 0;
}

void miss_sprite(void)
{
  if (missed < MAX_MISS) {
    missed++;
    streak = 0;
  } else {
    gm_st = END_GAME;
  }
}

int is_sprite_in_range(sprite_t *sprite, int y1, int y2)
{
  return (sprite->rect.y > (y1 - percent_y(RECT_TOLERANCE)) &&
    (sprite->rect.y < (y2 + percent_y(RECT_TOLERANCE))));
}
