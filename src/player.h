#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>
#include "rect.h"

struct Controls {
  SDL_Keycode up;
  SDL_Keycode down;
  SDL_Keycode left;
  SDL_Keycode right;  
};

struct Player {
  struct Rect rect;
  struct Controls controls;
  int number;
  int points;
};

struct Players {
  struct Player *players;
  int count;
};

struct Player create_player1();
struct Player create_player2();
void move_player(struct Player *p, struct Players *ps, struct Rects rcb);
int set_player_velocity(SDL_Renderer* r, struct Players* p, SDL_Keycode code);
void render_points(SDL_Renderer *renderer, const struct Player *p);
void check_player_collision(struct Player *p, struct Players *ps);
#endif
