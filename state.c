#include "state.h"

void state_init(void)
{
  // Initialisation of the SDL
  check_sdl_int(SDL_Init(SDL_INIT_VIDEO), "SDL_Init error");
  // Init the window
  win = SDL_CreateWindow("TapBerry",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         WINDOW_WIDTH, WINDOW_HEIGHT,
                         SDL_WINDOW_SHOWN);
  check_ptr(win, "SDL_CreateWindow error");
  // Get the width and height of the created window (probably different then
  // Init the renderer
  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED |
                                SDL_RENDERER_TARGETTEXTURE);
  check_ptr(ren, "SDL_CreateRenderer error");
  SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(ren, 240, 246, 255, 255);
  // Init the background
  background = load_surface("images/load_background.bmp");
  menu_init();
}

void menu_init(void) {
  // Set game state
  gm_st = IN_MENU;
  // Set initial difficulty
  DIFFICULTY = 10;
  GRAVITY = 8;
  // Set initial buttons to up
  //button_press.left = button_press.middle = button_press.right = 1;
}

void state_destroy(void)
{
    // Destroy all sprites
    apply_to_all_sprites(&destroy_sprite);
    // Destroy all surfaces
    apply_to_all_surfaces(&destroy_surface);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
}

void check_status(int frame_counter)
{
  printf("frame counter is %i\n", frame_counter);
  switch (frame_counter) {
    case 150:
      GRAVITY = 16;
      DIFFICULTY = 7;
    case 350:
      GRAVITY = 19;
      DIFFICULTY = 5;
    case 600:
      GRAVITY = 23;
      DIFFICULTY = 3;
  }
  if (missed > 5 && gm_st == IN_GAME) {
    gm_st = END_GAME;
  }
}
