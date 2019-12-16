learn_sdl:
	gcc main.c -o play -I include -L lib -l SDL2-2.0.0 -Werror -pedantic -Wall -Wextra
