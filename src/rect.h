#ifndef RECT_H
#define RECT_H
#include <SDL2/SDL.h>

struct Rect {
  SDL_Rect shape;
  int color[4];
  int x_velocity;
  int y_velocity;
};

struct Rects {
  struct Rect *rects;
  int size;
};

struct Rect create_rect(int x, int y, int w, int h, int r, int g, int b, int a);
struct Rect create_empty_rect();
void render_rect(SDL_Renderer *renderer, struct Rect *r);
void move_rect(struct Rect *r, struct Rects rc, int key);
int set_velocity(SDL_Renderer* r, struct Rect* rect, SDL_Keycode code);
#endif
