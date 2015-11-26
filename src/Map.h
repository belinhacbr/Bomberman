#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>

#include "Bomb.h"
#include "Item.h"

#define BOMB        'b'
#define EMPTY       '_'
#define SNOWMAN     'S'
#define ICE         '#'
#define FIRE        'F'

using namespace std;

class Map {
    private:
        int * map;
        int width;
        int height;
    public:
        list <Bomb * > bombs;
        list <Item * > itens;
        Map(int width, int height);
        void loadMap(const char *fileName);
        void createItemlist();
        int get(int lin, int col);
        void set(int lin, int col, int val);
        void print();
        void paint(SDL_Surface * bg, SDL_Surface * ice, int live);
        void moveAnimation();
        void action();
        bool passThrough(int lin,int col);
        void pickItem(int lin,int col, int item);
};

#endif
