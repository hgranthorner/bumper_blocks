#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 640

int move_rect(SDL_Renderer* r, SDL_Rect *rect, SDL_Keycode code)
{
  switch (code)
  {
  case SDLK_UP:
    rect->y -= 10;
    SDL_Log("Current y: %d\n", rect->y);
    break;
  case SDLK_RIGHT:
    rect->x += 10;
    SDL_Log("Current x: %d\n", rect->x);
    break;
  case SDLK_DOWN:
    rect->y += 10;
    SDL_Log("Current y: %d\n", rect->y);    
    break;
  case SDLK_LEFT:
    rect->x -= 10;
    SDL_Log("Current x: %d\n", rect->x);
    break;
  default:
    return 1;
  }

  printf("Moving square.\n");
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderClear(r);
  SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
  SDL_RenderFillRect(r, rect);
  SDL_RenderPresent(r);
  return 0;
}

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

  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) goto err;
  
  SDL_Rect rect;
  rect.x = 50;
  rect.y = 50;
  rect.w = 100;
  rect.h = 100;

  for (;;)
  {
    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        break;
      }
      if (e.type == SDL_KEYDOWN)
      {
        if (move_rect(renderer, &rect, e.key.keysym.sym) == 1)
        {
          switch (e.key.keysym.sym)
          {
          case SDLK_0:
            SDL_Log("Pressed 0.\n");
            break;
          default:
            break;
          }
        }
      }
      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        if (SDL_RenderFillRect(renderer, &rect) < 0) goto err;
        SDL_RenderPresent(renderer);
      }
      
    }
  }

  SDL_DestroyWindow(win);
  SDL_Quit();

  printf("Closing...\n");
  return 0;

 err:
  printf("There was an error: %s\n", SDL_GetError());
  SDL_Quit();
  return -1;
}
