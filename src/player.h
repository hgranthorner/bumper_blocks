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
  int key;
};

struct Players {
  struct Player *players;
  int count;
};

struct Player create_player1();
struct Player create_player2();
void move_player(struct Player *p, struct Players *ps, struct Rects rc, int key);
int set_player_velocity(SDL_Renderer* r, struct Players* p, SDL_Keycode code);
#endif
