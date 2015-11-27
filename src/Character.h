#ifndef CHARACTER_H
#define CHARACTER_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>
#include <iostream>
#include <list>
using namespace std;

#include "Bomb.h"

#define step 8

#define STOP    0
#define FRONT   1
#define LEFT    2
#define BACK    3
#define RIGHT   4
#define DEAD    5
#define WIN     6
#define LOSE    7

#define DEAD_TIME  8
#define IMUNE_TIME 32

class Character {
    private:
    public:
        int x;
        int y;
        int dx0;
        int dy0;
        int frame;
        int state;
        int life;
        int colorkey;
        int sprite_size;
        //int clear;
        Character(int x, int y, int dx0, int dy0, int sprite_size);
        bool collide(Character *c);
        bool collide(int x, int y);
        virtual void moveAnimation() = 0;
        virtual void die() = 0;
};


class Player : public Character {
    private:
    public:
        int imuneTime;
        int deadTime;
        bool flic;
        Player(int x, int y, int dx0, int dy0, int sprite_size);
        int bombNumber;
        int bombRange;
        void handleControl(list<int> &pressing);
        virtual void moveAnimation();
        virtual void die();
};

class Enemy : public Character {
    private:
    public:
        int routetype;
        int route;
        Enemy(int x, int y, int routetype, int dx0,int dy0, int sprite_size);
        void action ();
        virtual void moveAnimation();
        virtual void die();
        void killPlayer();
};

#endif
