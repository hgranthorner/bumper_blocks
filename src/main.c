#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <malloc/malloc.h>

#include "rect.h"
#include "consts.h"
#include "player.h"

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

  struct Players player_container;
  player_container.count = 2;
  
  struct Player players[] = { create_player1(), create_player2() };
  player_container.players = players;
  
  struct Rect green_rect = create_rect(50, 50, 100, 100, 0, 255, 0, 255);
  struct Rect blue_rect = create_rect(600, 600, 100, 100, 0, 0, 255, 255);
  struct Rect red_rect = create_rect(100, 600, 100, 100, 255, 0, 0, 255);

  struct Rects rect_container;
  rect_container.size = 3;
  rect_container.rects = (struct Rect *) malloc(sizeof(struct Rect) * 3);
  rect_container.rects[0] = green_rect;
  rect_container.rects[1] = blue_rect;
  rect_container.rects[2] = red_rect;
  
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
        if (set_player_velocity(renderer, &player_container, e.key.keysym.sym) == 1)
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

    for (int i = 0; i < player_container.count; ++i)
    {
      move_player(&player_container.players[i], &player_container, rect_container);
      render_rect(renderer, &player_container.players[i].rect);
      render_points(renderer, &player_container.players[i]);
    }
    
    for (int i = 0; i < rect_container.size; ++i)
    {
      render_rect(renderer, &rect_container.rects[i]);
    }
    
    const int end_frame_time = SDL_GetTicks();
    SDL_Delay(max(10, render_timer - (end_frame_time - start_frame_time)));
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
