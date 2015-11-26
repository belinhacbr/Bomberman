bomberman:	src/main.cpp
	g++ `sdl-config --cflags --libs` src/main.cpp -o Bomberman -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -std=c++11

clean:
	rm Bomberman

run: 
	./Bomberman