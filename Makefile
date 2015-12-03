Bomberman_unix:	
	g++ `sdl-config --cflags --libs` src/main.cpp src/global.cpp src/Bomb.cpp src/Map.cpp src/Item.cpp src/Character.cpp -o Bomberman_unix -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -std=c++0x

clean:
	rm Bomberman_unix

run: 
	./Bomberman_unix