#include "rect.h"
#include "consts.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

struct Rect create_rect(int x, int y, int w, int h, int r, int g, int b, int a)
{
  struct Rect rect;
  rect.color[0] = r;
  rect.color[1] = g;
  rect.color[2] = b;
  rect.color[3] = a;
  SDL_Rect sdl_rect = { x, y, w, h };
  rect.shape = sdl_rect;
  rect.x_velocity = 0;
  rect.y_velocity = 0;
  return rect;
}

struct Rect create_empty_rect()
{
  return create_rect(0,0,0,0,0,0,0,0);
}

void render_rect(SDL_Renderer *renderer, struct Rect *r)
{
  SDL_SetRenderDrawColor(renderer,
                         r->color[0],
                         r->color[1],
                         r->color[2],
                         r->color[3]);
  SDL_RenderFillRect(renderer, &r->shape);
}
