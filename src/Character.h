#ifndef CHARACTER_H
#define CHARACTER_H


#include <SDL.h>
/*#include <SDL_image.h>
#include <SDL_ttf.h>*/
#include <list>
#include <iostream>
#include <list>
using namespace std;

#include "bomb.h"

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
        int frame;
        int state;
        int life;
        //int clear;
        Character(int x, int y);
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
        Player(int x, int y);
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
        SDL_Surface * img1;
        SDL_Surface * img2;
        SDL_Surface * img3;
        Enemy(int x, int y,SDL_Surface * img1, SDL_Surface *img2, SDL_Surface * img3, int routetype);
        void action ();
        virtual void moveAnimation();
        virtual void die();
        void killPlayer();
};

#endif
