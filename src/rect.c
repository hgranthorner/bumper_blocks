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
  SDL_Rect sdl_rect = {
                       x,
                       y,
                       w,
                       h
  };
  rect.shape = sdl_rect;
  rect.x_velocity = 0;
  rect.y_velocity = 0;
  return rect;
}

struct Rect create_empty_rect()
{
  return create_rect(0,0,0,0,0,0,0,0);
}

void render_rects(SDL_Renderer *renderer, struct Rects *rc)
{
  for (int i = 0; i < rc->size; ++i)
  {
    if (rc->rects[i].shape.x < 0)
    {
      rc->rects[i].shape.x = 0;
      rc->rects[i].x_velocity = 0;
    }
    else if (rc->rects[i].shape.x + rc->rects[i].shape.w > WIDTH)
    {
      rc->rects[i].shape.x = WIDTH - rc->rects[i].shape.w;
      rc->rects[i].x_velocity = 0;
    }
    else rc->rects[i].shape.x += rc->rects[i].x_velocity;
    
    if (rc->rects[i].shape.y < 0)
    {
      rc->rects[i].shape.y = 0;
      rc->rects[i].y_velocity = 0;
    }
    else if (rc->rects[i].shape.y + rc->rects[i].shape.h > HEIGHT)
    {
      rc->rects[i].shape.y = WIDTH - rc->rects[i].shape.h;
      rc->rects[i].y_velocity = 0;
    }
    else rc->rects[i].shape.y += rc->rects[i].y_velocity;
    
    SDL_SetRenderDrawColor(renderer, rc->rects[i].color[0], rc->rects[i].color[1], rc->rects[i].color[2], rc->rects[i].color[3]);
    SDL_RenderFillRect(renderer, &rc->rects[i].shape);      
  }
}
