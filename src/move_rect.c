#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int move_rect(SDL_Renderer* r, SDL_Rect* rect, SDL_Keycode code)
{
  switch (code)
  {
  case SDLK_UP:
    rect->y -= 10;
    break;
  case SDLK_RIGHT:
    rect->x += 10;
    break;
  case SDLK_DOWN:
    rect->y += 10;
    break;
  case SDLK_LEFT:
    rect->x -= 10;
    break;
  default:
    return 1;
  }

  return 0;
}
