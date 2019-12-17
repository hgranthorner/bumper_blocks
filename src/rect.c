#include "rect.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

struct Rect create_rect(int x, int y, int w, int h, int r, int g, int b, int a)
{
  struct Rect rect;
  rect.color[0] = r;
  rect.color[1] = g;
  rect.color[2] = b;
  rect.color[3] = a;
  SDL_Rect sdl_rect = {
                       x,
                       y,
                       w,
                       h
  };
  rect.shape = sdl_rect;

  return rect;
}

struct Rect create_empty_rect()
{
  return create_rect(0,0,0,0,0,0,0,0);
}

void render_rects(SDL_Renderer *renderer, struct Rects rect_container)
{
  for (int i = 0; i < rect_container.size; ++i)
  {
    SDL_SetRenderDrawColor(renderer, rect_container.rects[i].color[0], rect_container.rects[i].color[1], rect_container.rects[i].color[2], rect_container.rects[i].color[3]);
    SDL_RenderFillRect(renderer, &rect_container.rects[i].shape);      
  }
}
