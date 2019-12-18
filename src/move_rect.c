#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "rect.h"

int move_rect(SDL_Renderer* r, struct Rect* rect, SDL_Keycode code)
{
  switch (code)
  {
  case SDLK_UP:
    rect->y_velocity += -1;
    break;
  case SDLK_RIGHT:
    rect->x_velocity += 1;
    break;
  case SDLK_DOWN:
    rect->y_velocity += 1;
    break;
  case SDLK_LEFT:
    rect->x_velocity += -1;
    break;
  default:
    return 1;
  }

  return 0;
}
