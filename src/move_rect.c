#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int move_rect(SDL_Renderer* r, SDL_Rect *rect, SDL_Keycode code)
{
  switch (code)
  {
  case SDLK_UP:
    rect->y -= 10;
    SDL_Log("Current y: %d\n", rect->y);
    break;
  case SDLK_RIGHT:
    rect->x += 10;
    SDL_Log("Current x: %d\n", rect->x);
    break;
  case SDLK_DOWN:
    rect->y += 10;
    SDL_Log("Current y: %d\n", rect->y);    
    break;
  case SDLK_LEFT:
    rect->x -= 10;
    SDL_Log("Current x: %d\n", rect->x);
    break;
  default:
    return 1;
  }

  Uint8 red   = rand() % 255;
  Uint8 blue  = rand() % 255;
  Uint8 green = rand() % 255;

  printf("Moving square.\n");
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r, red, blue, green, 255);
  SDL_RenderFillRect(r, rect);
  SDL_RenderPresent(r);
  return 0;
}
