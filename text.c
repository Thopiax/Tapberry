#include "text.h"

TTF_Font *font;

void init_text(void) {
  //For text display
  check_sdl_int(TTF_Init(), TTF_GetError());
  font = TTF_OpenFont("code.ttf", 24);
  color = (SDL_Color) {255, 0, 0, 0};
}

void render_text(char *message, int x, int y, SDL_Color color, int blended) {
  SDL_Surface *message_surface = TTF_RenderText_Solid(font, message, color);
  SDL_Rect message_rect;
  message_rect = get_rect_from_surface(percent_x(x), percent_y(y), message_surface);
  check_ptr(message_surface, "Unable to create surface message");
  if(blended) {
    //Slower but looks better
    message_surface = TTF_RenderText_Blended(font, message, color);
  } else {
    //Faster but looks bad
    message_surface = TTF_RenderText_Solid(font, message, color);
  }
  message_surface = SDL_ConvertSurfaceFormat(message_surface, PIXEL_FORMAT, 0);
  check_ptr(message_surface, "Unable to convert the text message surface");
  SDL_UpdateTexture(screen_texture, &message_rect, message_surface->pixels,
                    message_surface->pitch);
}

void text_quit(void) {
  //Close font
  TTF_CloseFont(font);
  //Quit ttf
  TTF_Quit();
}
