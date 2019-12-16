#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 640

int main(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    exit(1);
  }
  printf("Initialized SDL.\n");
  SDL_Window* win = SDL_CreateWindow("Title",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     WIDTH,
                                     HEIGHT,
                                     SDL_WINDOW_OPENGL);

  if (!win)
  {
    printf("Error rendering window: %s\n", SDL_GetError());
    SDL_Quit();
    exit(1);
  }
  printf("Rendered window.\n");

  SDL_Event e;
  int quit = 0;
  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        quit = 1;
      }
      if (e.type == SDL_KEYDOWN)
      {
        quit = 1;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        quit = 1;
      }
    }
  }

  SDL_DestroyWindow(win);
  SDL_Quit();

  printf("Closing...\n");
  return 0;
}
