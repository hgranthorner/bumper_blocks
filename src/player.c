#include "player.h"

#include <stdio.h>
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
  p.number = 1;
  p.points = 10;
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
  p.number = 2;
  p.points = 10;
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
    p->rect.x_velocity = -p->rect.x_velocity / 2;
    p->points -= 1;
  }
  else if (p->rect.shape.x + p->rect.shape.w > WIDTH)
  {
    p->rect.shape.x = WIDTH - p->rect.shape.w;
    p->rect.x_velocity = -p->rect.x_velocity / 2;
    p->points -= 1;
  }
  else p->rect.shape.x += p->rect.x_velocity;

  if (p->rect.shape.y < 0)
  {
    p->rect.shape.y = 0;
    p->rect.y_velocity = -p->rect.y_velocity / 2;
    p->points -= 1;
  }
  else if (p->rect.shape.y + p->rect.shape.h > HEIGHT)
  {
    p->rect.shape.y = HEIGHT - p->rect.shape.h;
    p->rect.y_velocity = -p->rect.y_velocity / 2;
    p->points -= 1;
  }
  else p->rect.shape.y += p->rect.y_velocity;
}

void check_player_collision(struct Player *p, struct Players *ps)
{
  for (int i = 0; i < ps->count; ++i)
  {
    if (p->number == ps->players[i].number) continue;

    struct Rect *current_rect = &ps->players[i].rect;
    SDL_bool result = SDL_HasIntersection(&p->rect.shape,
                                          &current_rect->shape);
    if (result == SDL_TRUE)
    {
      int delta_x = (int) (
                           abs(p->rect.x_velocity)
                           + abs(current_rect->x_velocity)
                     ) / 2;
      int delta_y = (int) (
                           abs(p->rect.y_velocity)
                           + abs(current_rect->y_velocity)
                     ) / 2;

      int denom_x = p->rect.x_velocity == 0
        ? 1
        : abs(p->rect.x_velocity);
      int denom_y = p->rect.y_velocity == 0
        ? 1
        : abs(p->rect.y_velocity);
      
      int direction_x = (int) -(p->rect.x_velocity / denom_x);
      int direction_y = (int) -(p->rect.y_velocity / denom_y);
      
      p->rect.shape.x += delta_x * direction_x;
      p->rect.shape.y += delta_y * direction_y;
      p->rect.x_velocity = delta_x * direction_x;
      p->rect.y_velocity = delta_y * direction_y;

      current_rect->shape.x += -(delta_x * direction_x);
      current_rect->shape.y += -(delta_y * direction_y);
      current_rect->x_velocity = -(delta_x * direction_x);
      current_rect->y_velocity = -(delta_y * direction_y);
    }
  }
}

void move_player(struct Player *p, struct Players *ps, struct Rects rc)
{
  check_rect_collision(p, rc);
  check_player_collision(p, ps);
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

void render_points(SDL_Renderer *renderer, const struct Player *p)
{
  for (int i = 0; i < p->points; ++i)
  {
    int x = p->number == 1
      ? p->rect.shape.w
      : WIDTH - (p->rect.shape.w * 2);
    int y = (HEIGHT / 20) * (10 - i);
    struct Rect rect = create_rect(x, y,
                              PLAYER_LENGTH / 4,
                              PLAYER_LENGTH / 4,
                              0, 0, 0, 255);
    if (p->number == 1) rect.color[0] = 255;
    else if (p->number == 2) rect.color[2] = 255;

    render_rect(renderer, &rect);
  }
}
