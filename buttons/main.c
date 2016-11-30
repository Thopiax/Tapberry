#include "main.h"

SDL_Surface *screen = NULL, *background = NULL, *circle = NULL;
SDL_Surface *blue_circle = NULL, *green_circle = NULL, *red_circle = NULL;
SDL_Surface *tapped = NULL;
SDL_Rect position, background_position, blue_position, green_position, red_position, tapped_position, old_position;

 
int main(int argc, char *argv[])
{  
    init();
    // Running the program
    anime();
    clean_up(); 
    return EXIT_SUCCESS;
}

void init(void) {
    // Initialisation of the SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    //Opening the window 
    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BITS_PER_PIXEL, SDL_HWSURFACE | SDL_DOUBLEBUF); 
    if(screen == NULL) {
      fprintf(stderr, "Impossible to load video mode: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
    
    load_images();
   
    SDL_WM_SetCaption("TapBerry", NULL); 
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 17,206, 112));
    
    init_coordinates();    

    //remove circle image background
    SDL_SetColorKey(circle, SDL_SRCCOLORKEY, SDL_MapRGB(circle->format, 1, 0, 102));
    
    //Showing background on screen
    SDL_BlitSurface(background, NULL, screen, &background_position);
    //Showing circle on screen
    /*
    SDL_BlitSurface(circle, NULL, screen, &position);
    SDL_BlitSurface(red_circle, NULL, screen, &red_position);
    SDL_BlitSurface(green_circle, NULL, screen, &green_position);
    SDL_BlitSurface(blue_circle, NULL, screen, &blue_position);
    */
    //Update screen with new colour
    SDL_Flip(screen);   
}

void setup_buttons() {
 
  puts("Button test beggining");

  if(wiringPiSetup()) {
    perror("wiringPi unable to setup");
    exit(1);
  }

}

void anime(void) {
  int moveY = 1;
  SDL_Rect background_position_c, position_c;
  SDL_Rect clipper;
  int button = 4; //GPIO pin
  int frame_start, frame_delay; //for use with SDL_GetTicks();

  while(1) {
    clipper.x = position.x;
    clipper.h = position.y;
    clipper.h = circle->h;
    clipper.w = circle->w;
    SDL_BlitSurface(background, &clipper, screen, &old_position);
    SDL_BlitSurface(circle, NULL, screen, &position);
/*
    SDL_SetClipRect(screen, &clipper);
    
    background_position_c.x = background_position.x;
    background_position_c.y = background_position.y;
    
    position_c.x = background_position.x;
    position_c.y = background_position.y;

    SDL_BlitSurface(background, NULL, screen, &background_position_c);
    SDL_SetClipRect(screen, NULL);
    SDL_BlitSurface(circle, NULL, screen, &position_c);
*/
    old_position.x = position.x;
    old_position.y = position.y;

    //Move if in the screen
    if(moveY) {
      position.y++;
    }
   
    //Stop moving when out of the screen
    if(position.y == screen->h) {
      moveY = 0;
    }

    SDL_Flip(screen);
    input_handle();
    //SDL_Delay(10);    
  }
}
 
void input_handle(void)
{
    int wait = 1;
    SDL_Event event; 
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
          //If the user clicked on the cross to exit
          case SDL_QUIT:
            SDL_Quit();
            exit(0);
            break;
          //If a key was pressed
          case SDL_KEYDOWN:
            //Find what key was pressed
            switch (event.key.keysym.sym)
            {
              case SDLK_LEFT_COL: /* Appui sur la touche Echap, on arrête le programme */
                press_left();
                break;
              case SDLK_DOWN: /* Appui sur la touche Echap, on arrête le programme */
                press_middle();
                break;
              case SDLK_RIGHT_COL: /* Appui sur la touche Echap, on arrête le programme */
                press_right();
                break;
            }
            //Make tapped appear
            SDL_SetAlpha(tapped, SDL_SRCALPHA, 80);
            SDL_BlitSurface(tapped, NULL, screen, &tapped_position);
            SDL_Flip(screen);
            break;
            //If the key is going back up
            case SDL_KEYUP:
              //Make tapped disappear
              SDL_SetAlpha(tapped, SDL_SRCALPHA, 0);
              SDL_BlitSurface(tapped, NULL, screen, &tapped_position);
              SDL_Flip(screen);
              break;
        }
  }
}
    
void press_left(void) {
  tapped_position = red_position; 
}
    
void press_middle(void) {
  tapped_position = green_position;
}
    
void press_right(void) {
  tapped_position = blue_position;
}

void clean_up(void) {
  SDL_FreeSurface(blue_circle);
  SDL_FreeSurface(green_circle);
  SDL_FreeSurface(red_circle);
  SDL_FreeSurface(tapped);
  SDL_FreeSurface(circle);
  SDL_FreeSurface(background);
  
  // Stopping the SDL
  SDL_Quit(); 
}

void load_images(void) {
  background = SDL_LoadBMP("../tapberry_background.bmp");
  circle = SDL_LoadBMP("../circle.bmp");
  blue_circle = SDL_LoadBMP("../blue_circle.bmp");
  green_circle = SDL_LoadBMP("../green_circle.bmp");
  red_circle = SDL_LoadBMP("../red_circle.bmp");
  tapped = SDL_LoadBMP("../tapped.bmp");
}

void init_coordinates(void) {
    //Coordinates of the circle
    position.x = (WINDOW_WIDTH / 2) - (CIRCLE_WIDTH / 2);
    position.y = (WINDOW_HEIGHT / 2) - (CIRCLE_HEIGHT / 2);

    old_position.x = 0;
    old_position.y = 0;

    //Coordinates of color circles
    red_position.x = 0;
    green_position.x = (WINDOW_WIDTH / 2) - (CIRCLE_WIDTH / 2);
    blue_position.x = 0.7 * WINDOW_WIDTH;
    
    float vertical_color_position = 0.8 * WINDOW_HEIGHT;
    red_position.y = vertical_color_position;
    green_position.y = vertical_color_position;
    blue_position.y = vertical_color_position;

    //Coordinates of the background
    background_position.x = 0;
    background_position.y = 0;
}
