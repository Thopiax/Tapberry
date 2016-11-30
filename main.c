#include "main.h"

// DECLARE EXTERN VARIABLES
SDL_Window *win;
SDL_Renderer *ren;
SDL_Surface *background;
game_state_t gm_st;
int streak;
int missed;
int display_score = 0;
int score;
int score_mod = 0;
int DIFFICULTY;
int GRAVITY;
SDL_Color color;
int frame_counter;
pressed_t button_press;

sprite_t *all_sprites[MAX_NUM_OF_SPRITES];
SDL_Surface *all_surfaces[IMAGE_COUNT];
SDL_Texture *screen_texture;

int main(int argc, char *argv[])
{
  setup_buttons();
  state_init();
  // initiate everything
  init_text();
  init_texture();
  init_surfaces();
  // Running the program
  anime();
  clean_up();
  return EXIT_SUCCESS;
}

void anime(void) {
  frame_counter = 0;
  // make the random key
  srand (time(NULL));
  while (1) {
    // Check game status
    check_status(frame_counter);
    // get the game state
    switch (gm_st) {
      case IN_GAME:
        if(frame_counter == 0) {
          score = 0;
        }
        frame_counter++;
        // Make a new line of fruit
        make_new_line();
        //Move sprites down
        apply_to_all_sprites(&update_sprite_pos);
        break;
      case END_GAME:
        menu_init();
        apply_to_all_sprites(&destroy_sprite);
        display_score = 1;
        missed = 0;
        frame_counter = 0;
        streak = 0;
        break;
      case IN_MENU:
        background = all_surfaces[MENU_BACKGROUND_IND];
        break;
    }
    input_handle();
    //Update the screen
    game_render();
    // Delay the screen
    //SDL_Delay( 1000 / FRAMES_PER_SECOND );
  }
}

void make_new_line(void)
{
  if (get_next_sprite_num() >= 0) {
    // get random number based on the difficulty
    int r = rand() % DIFFICULTY;
    if (r == 0) {
      if (streak < 10) {
        sprite_init_rand(NULL);
        score_mod = 1;
        color = (SDL_Color) {255, 0, 0, 0};
      } else {
        sprite_init_rand(all_surfaces[BANANA_IND]);
        score_mod = 2;
        color = (SDL_Color) {200, 200, 0, 0};
      }
    }
  }
}

void game_render(void)
{
  int blended = 1;
  // Add the background
  SDL_UpdateTexture(screen_texture, NULL, background->pixels,
                    background->pitch);
  if (gm_st == IN_GAME) {
    // Add the sprites
    apply_to_all_sprites(&render_sprite);
    // Render the skips
    render_miss();
  }
  if (gm_st == IN_MENU && display_score) {
    char score_text[20];
    sprintf(score_text, "Your score is %d", score);
    //Trying to render the score but this is not working. Will figure out why later
    render_text(score_text, 20, 67, color, blended);
  }
  if(streak > 0) {
    char streak_msg[20];
    sprintf(streak_msg, "%d", streak);
    render_text(streak_msg, 92, 95, color, blended);
  }
  // Clear the renderer
  SDL_RenderClear(ren);
  // Copy the texture
  SDL_RenderCopy(ren, screen_texture, NULL, NULL);
  // and render
  SDL_RenderPresent(ren);
}

void input_handle(void)
{
  button_press.left   |= digitalRead(BUTTON_L);
  button_press.middle |= digitalRead(BUTTON_M);
  button_press.right  |= digitalRead(BUTTON_R);
  button_press.end    |= digitalRead(BUTTON_E);

  if(button_press.left) {
    puts("started");
    start_game(&add_to_render_sprite);
  }

  if(!(frame_counter % 3)) {
    get_pressed();
  }

  if(button_press.end) {
    clean_up();
    exit(EXIT_SUCCESS);
  }
}

void get_pressed(void)
{
  //Go through all sprite to find if one is in the area for a hit
  if (button_press.left) {
    puts("pressed left");
    check_hit(LEFT_COL);
    button_press.left = 0;
  }
  if (button_press.middle) {
    puts("pressed middle");
    check_hit(MIDDLE_COL);
    button_press.middle = 0;
  }
  if (button_press.right) {
    puts("pressed right");
    check_hit(RIGHT_COL);
    button_press.right = 0;
  }
}

void check_hit(col_pos_t col_pos)
{
  for(int i = 0; i < MAX_NUM_OF_SPRITES; i++) {
    sprite_t *spr = all_sprites[i];
    if(spr != NULL && spr->col_pos == col_pos && is_sprite_in_range(spr,
          percent_y(BUTTONS_Y), WINDOW_HEIGHT)) {
      if (spr->hit == 0) {
        // hit it, so delete the sprite
        spr->hit = 1;
        spr->to_render = 0;
        // and append to the streaks
        streak++;
        //Increase score
        score += score_mod;
        return;
      }
    }
  }
  miss_sprite();
}

void setup_buttons() {

  if(wiringPiSetup()) {
    perror("wiringPi unable to setup");
    exit(1);
  }

  pinMode(BUTTON_L, INPUT); //left set to input to be read
  pinMode(BUTTON_M, INPUT); //middle set to input to be read
  pinMode(BUTTON_R, INPUT); //right set to input to be read
  pinMode(BUTTON_E, INPUT); //end set to input to be read
}

void clean_up(void) {
  // Destroy the state
  state_destroy();
  //Close font and quit ttf
  text_quit();
  // Stopping the SDL
  SDL_Quit();
}
