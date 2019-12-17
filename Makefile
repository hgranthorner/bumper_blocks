learn_sdl:
	gcc -c src/move_rect.c -o src/move_rect.o
	gcc -c src/main.c -o src/main.o
	gcc src/move_rect.o src/main.o -o play -I include -L lib -l SDL2-2.0.0 -Werror -pedantic -Wall -Wextra
