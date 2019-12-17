#include <SDL2/SDL.h>

struct Rect {
  SDL_Rect shape;
  int color[4];
};

struct Rects {
  struct Rect *rects;
  int size;
};

struct Rect create_rect(int x, int y, int w, int h, int r, int g, int b, int a);
struct Rect create_empty_rect();
void render_rects(SDL_Renderer *renderer, struct Rects rect_container);
