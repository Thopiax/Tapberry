#ifndef CONFIG_H
#define CONFIG_H

/* INCLUSIONS */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

/* MACROS */
#define SDL_VERION 2
// WINDOW CONSTANTS
#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 460
#define START_LINE 15
#define RECT_TOLERANCE 3
#define DEFAULT_SCREEN_TOP    0
#define DEFAULT_SCREEN_BOTTOM 460
#define DEFAULT_SCREEN_LEFT_COL   0
#define DEFAULT_SCREEN_RIGHT_COL  320
#define PIXEL_FORMAT SDL_PIXELFORMAT_RGBA4444
// COLUMN POS
#define MAX_NUM_OF_SPRITES 10
#define IMAGE_COUNT 8
#define MAX_MISS 5
#define FRAMES_PER_SECOND 20
// TEXTURE INDICES
// BACKGROUNDS
#define MENU_BACKGROUND_IND 0
#define GAME_FOREGROUND_IND 1
// SPRITE IMAGES
#define BANANA_IND 2
#define BLKBRY_IND 3
#define BLUBRY_IND 4
#define RSPBRY_IND 5
#define CROSS_IND 6
#define BUTTONS_IND 7
#define BUTTONS_Y 75
#define BUTTONS_X 12
#define BUTTONS_W 75

/* ENUMS */
enum game_state { IN_MENU, IN_GAME, END_GAME };
enum col_pos { LEFT_COL = 15, MIDDLE_COL = 38, RIGHT_COL = 63};

/* TYPEDEFS */
typedef enum game_state game_state_t;
typedef enum col_pos    col_pos_t;
typedef struct sprite   sprite_t;
typedef struct pressed  pressed_t;

struct sprite {
  SDL_Surface *surface;
  SDL_Rect rect;
  col_pos_t col_pos;
  int id;
  int to_render;
  int hit;
};

struct pressed {
  int left, middle, right, end;
};

extern SDL_Window *win;
extern SDL_Renderer *ren;
extern SDL_Surface *background;
extern game_state_t gm_st;
extern int streak;
extern int missed;
extern int score;
extern int score_mod;
extern int DIFFICULTY;
extern int GRAVITY;
extern SDL_Color color;
extern pressed_t button_press;

extern sprite_t *all_sprites[MAX_NUM_OF_SPRITES];
extern SDL_Surface *all_surfaces[IMAGE_COUNT];
extern SDL_Texture *screen_texture;

#endif
