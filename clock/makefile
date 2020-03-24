.PHONY:clock clean
clock:clock.c
	gcc -Wall -O2 `sdl2-config --cflags` clock.c logo.o  -o clock `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
clean:
	-rm clock.o
	-rm clock.exe