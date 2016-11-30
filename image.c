#include "image.h"

void init_surfaces(void)
{
  all_surfaces[MENU_BACKGROUND_IND] = load_surface("images/menu_background.bmp");
  all_surfaces[GAME_FOREGROUND_IND] = load_surface("images/tapberry_foreground.png");
  check_sdl_int(SDL_SetSurfaceRLE(all_surfaces[GAME_FOREGROUND_IND], SDL_TRUE),
    "Unale to make the game foreground an RLE surface");
  all_surfaces[BANANA_IND]          = load_surface("images/banana.png");
  all_surfaces[BLKBRY_IND]          = load_surface("images/blackberry.png");
  all_surfaces[BLUBRY_IND]          = load_surface("images/blueberry.png");
  all_surfaces[RSPBRY_IND]          = load_surface("images/raspberry.png");
  all_surfaces[CROSS_IND]           = load_surface("images/cross.png");
  all_surfaces[BUTTONS_IND]         = load_surface("images/tapberry_buttons.png");
}

void init_texture(void)
{
  screen_texture = SDL_CreateTexture(ren,
                                      PIXEL_FORMAT,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      WINDOW_WIDTH, WINDOW_HEIGHT);
  check_ptr(screen_texture, "Failed to create screen texture");
  SDL_SetTextureAlphaMod(screen_texture, 255);
  SDL_SetTextureBlendMode(screen_texture, SDL_BLENDMODE_BLEND);
}

void destroy_surface(SDL_Surface *surface)
{
  SDL_FreeSurface(surface);
}
