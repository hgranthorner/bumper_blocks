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

// TODO: Figure out how to remove the "key" field
void move_rect(struct Rect *r, struct Rects rc, int key)
{
  for (int i = 0; i < rc.size; ++i)
  {
    if (i == key) continue;

    SDL_bool result = SDL_HasIntersection(&r->shape, &rc.rects[i].shape);
    if (result == SDL_TRUE)
    {
      r->shape.x -= r->x_velocity * 2;
      r->shape.y -= r->y_velocity * 2;
      r->x_velocity = -r->x_velocity / 2;
      r->y_velocity = -r->y_velocity / 2;
    }
  }
  if (r->shape.x < 0)
  {
   r->shape.x = 0;
   r->x_velocity = 0;
  }
  else if (r->shape.x + r->shape.w > WIDTH)
  {
   r->shape.x = WIDTH - r->shape.w;
   r->x_velocity = 0;
  }
  else r->shape.x += r->x_velocity;

  if (r->shape.y < 0)
  {
   r->shape.y = 0;
   r->y_velocity = 0;
  }
  else if (r->shape.y + r->shape.h > HEIGHT)
  {
   r->shape.y = WIDTH - r->shape.h;
   r->y_velocity = 0;
  }
  else r->shape.y += r->y_velocity;
}

int set_velocity(SDL_Renderer* r, struct Rect* rect, SDL_Keycode code)
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
