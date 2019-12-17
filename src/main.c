#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <malloc/malloc.h>

#include "move_rect.h"
#include "rect.h"

#define WIDTH 640
#define HEIGHT 640
#define FPS 60
#define MAX(x, y) ((x) > (y) ? (x) : (y))

int main(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) goto err;

  printf("Initialized SDL.\n");
  SDL_Window* win = SDL_CreateWindow("Title",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     WIDTH,
                                     HEIGHT,
                                     SDL_WINDOW_OPENGL);

  if (!win) goto err;
  printf("Rendered window.\n");

  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) goto err;
  
  struct Rect rect = create_rect(50, 50, 100, 100, 255, 0, 0, 255);
  struct Rect blue_rect = create_rect(100, 100, 100, 100, 0, 0, 255, 255);
  struct Rect falling_rect = create_rect(400, 0, 100, 100, 0, 255, 0, 255);

  struct Rects rect_container;
  rect_container.size = 3;
  rect_container.rects = (struct Rect *) malloc(sizeof(struct Rect) * 3);
  rect_container.rects[0] = rect;
  rect_container.rects[1] = blue_rect;
  rect_container.rects[2] = falling_rect;
  
  const int render_timer = roundf(1000.0f / (float) FPS);

  for (;;)
  {
    SDL_Event e;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    const int start_frame_time = SDL_GetTicks();    
    
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_KEYDOWN)
      {
        if (move_rect(renderer, &rect_container.rects[0].shape, e.key.keysym.sym) == 1)
        {
          struct Rect *temp_rect;
          switch (e.key.keysym.sym)
          {
          case SDLK_0:
            SDL_Log("Pressed 0.\n");
            break;
          case SDLK_n:
            temp_rect = rect_container.rects;
            rect_container.size += 1;
            rect_container.rects = (struct Rect *) malloc(sizeof(struct Rect) * rect_container.size);
            if (!rect_container.rects) goto malloc_err;
            for (int j = 0; j < rect_container.size - 1; ++j)
            {
              rect_container.rects[j] = temp_rect[j];
            }
            rect_container.rects[rect_container.size - 1] = create_rect(400, 400, 100, 100, 100, 100, 100, 255);
            free(temp_rect);
            break;
          default:
            break;
          }
        }
      }
      if (e.type == SDL_QUIT)
      {
        break;
      }
    }
    
    render_rects(renderer, rect_container);
    
    const int end_frame_time = SDL_GetTicks();
    SDL_Delay(MAX(10, render_timer - (end_frame_time - start_frame_time)));
    SDL_RenderPresent(renderer);
 }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
  free(rect_container.rects);

  printf("Closing...\n");
  return 0;
 malloc_err:
  free(rect_container.rects);
 err:
  printf("There was an error: %s\n", SDL_GetError());
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);  
  SDL_Quit();
  return -1;
}
