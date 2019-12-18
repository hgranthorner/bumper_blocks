#include "player.h"

#include <SDL2/SDL.h>
#include "rect.h"
#include "consts.h"

struct Player create_player1()
{
  struct Player p;
  struct Controls c = { .up    = SDLK_UP,
                        .down  = SDLK_DOWN,
                        .left  = SDLK_LEFT,
                        .right = SDLK_RIGHT };
  p.controls = c;
  p.key = 0;
  int half_p = PLAYER_LENGTH / 2;
  p.rect = create_rect((WIDTH / 5) - half_p,
                       (HEIGHT / 2) - half_p,
                       PLAYER_LENGTH,
                       PLAYER_LENGTH,
                       255, 0, 0, 255);

  return p;
}

struct Player create_player2()
{
  struct Player p;
  struct Controls c = { .up    = SDLK_w,
                        .down  = SDLK_s,
                        .left  = SDLK_a,
                        .right = SDLK_d };
  p.controls = c;
  p.key = 0;
  int half_p = PLAYER_LENGTH / 2;
  p.rect = create_rect((WIDTH / 5) * 4 - half_p,
                       (HEIGHT / 2) - half_p,
                       PLAYER_LENGTH,
                       PLAYER_LENGTH,
                       0, 0, 255, 255);

  return p;
}

void check_rect_collision(struct Player *p, struct Rects rc)
{
  for (int i = 0; i < rc.size; ++i)
  {
    SDL_bool result = SDL_HasIntersection(&p->rect.shape, &rc.rects[i].shape);
    if (result == SDL_TRUE)
    {
      p->rect.shape.x -= p->rect.x_velocity * 2;
      p->rect.shape.y -= p->rect.y_velocity * 2;
      p->rect.x_velocity = -p->rect.x_velocity / 2;
      p->rect.y_velocity = -p->rect.y_velocity / 2;
    }
  }
  if (p->rect.shape.x < 0)
  {
    p->rect.shape.x = 0;
    p->rect.x_velocity = 0;
  }
  else if (p->rect.shape.x + p->rect.shape.w > WIDTH)
  {
    p->rect.shape.x = WIDTH - p->rect.shape.w;
    p->rect.x_velocity = 0;
  }
  else p->rect.shape.x += p->rect.x_velocity;

  if (p->rect.shape.y < 0)
  {
    p->rect.shape.y = 0;
    p->rect.y_velocity = 0;
  }
  else if (p->rect.shape.y + p->rect.shape.h > HEIGHT)
  {
    p->rect.shape.y = HEIGHT - p->rect.shape.h;
    p->rect.y_velocity = 0;
  }
  else p->rect.shape.y += p->rect.y_velocity;
}

void move_player(struct Player *p, struct Players *ps, struct Rects rc, int key)
{
  check_rect_collision(p, rc);
}

int set_player_velocity(SDL_Renderer* r, struct Players* p, SDL_Keycode code)
{
  int result = 1;
  for (int i = 0; i < p->count; ++i)
  {
    int *x_vel = &p->players[i].rect.x_velocity;
    int *y_vel = &p->players[i].rect.y_velocity;
    struct Controls *c = &p->players[i].controls;
    if (c->up == code)
    {
      *y_vel += *y_vel < -12 ? 0 : -3;
      result = 0;
    }
    else if (c->right == code)
    {
      *x_vel += *x_vel > 12 ? 0 : 3;
      result = 0;
    }
    else if (c->down == code)
    {
      *y_vel += *y_vel > 12 ? 0 : 3;
      result = 0;
    }
    else if (c->left == code)
    {
      *x_vel += *x_vel < -12 ? 0 : -3;
      result = 0;
    }
  }
  return result;
}
