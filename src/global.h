#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <SDL_audio.h>

#include <list>

#include "Character.h"
#include "Bomb.h"
#include "Item.h"
#include "Map.h"

#define NUM_SOUNDS 1 //2
#define SOUND_FREQUENCY 45000

#define delay       70
#define ENEMY_SPRITE_SIZE  32
#define GRID_SIZE 32
#define MAX_X 13
#define MAX_Y 11


using namespace std;


extern SDL_Thread *threadplayer;
extern SDL_Thread *threadenemy1;
extern SDL_Thread *threadenemy2;
extern SDL_Thread *threadenemy3;
extern SDL_Thread *threadtext;

extern Player *player;
extern Enemy *enemy;
extern Enemy *enemy2;
extern Enemy *enemy3;

extern Map map;
extern SDL_Color color;
extern SDL_Surface *screen;
extern SDL_Event event;

extern SDL_Surface *menuImage;
extern SDL_Surface *iconImage;
extern SDL_Surface *optionsImage;

extern SDL_Surface *mapImage;
extern SDL_Surface *item_sprite;
extern SDL_Surface *enemy_sprite;
extern SDL_Surface *fire_sprite;
extern SDL_Surface *player_sprite;

extern SDL_Surface * iceImage;

extern SDL_Surface *frontImage1;
extern SDL_Surface *frontImage2;
extern SDL_Surface *frontImage3;

extern SDL_Surface *rightImage1;
extern SDL_Surface *rightImage2;
extern SDL_Surface *rightImage3;

extern SDL_Surface *backImage1;
extern SDL_Surface *backImage2;
extern SDL_Surface *backImage3;

extern SDL_Surface *leftImage1;
extern SDL_Surface *leftImage2;
extern SDL_Surface *leftImage3;

extern SDL_Surface *deadImage1;
extern SDL_Surface *deadImage2;
extern SDL_Surface *deadImage3;

extern SDL_Surface *winImage1;
extern SDL_Surface *winImage2;
extern SDL_Surface *winImage3;

extern SDL_Surface *loseImage1;
extern SDL_Surface *loseImage2;
extern SDL_Surface *loseImage3;

extern SDL_Surface *bombImage1;
extern SDL_Surface *bombImage2;
extern SDL_Surface *bombImage3;

extern SDL_Surface *fireCenterImage1;
extern SDL_Surface *fireCenterImage2;
extern SDL_Surface *fireCenterImage3;
extern SDL_Surface *fireCenterImage4;

extern SDL_Surface *fireUpImage1;
extern SDL_Surface *fireUpImage2;
extern SDL_Surface *fireUpImage3;
extern SDL_Surface *fireUpImage4;

extern SDL_Surface *fireDownImage1;
extern SDL_Surface *fireDownImage2;
extern SDL_Surface *fireDownImage3;
extern SDL_Surface *fireDownImage4;

extern SDL_Surface *fireLeftImage1;
extern SDL_Surface *fireLeftImage2;
extern SDL_Surface *fireLeftImage3;
extern SDL_Surface *fireLeftImage4;

extern SDL_Surface *fireRightImage1;
extern SDL_Surface *fireRightImage2;
extern SDL_Surface *fireRightImage3;
extern SDL_Surface *fireRightImage4;

extern SDL_Surface *fireLeftMiddleImage1;
extern SDL_Surface *fireLeftMiddleImage2;
extern SDL_Surface *fireLeftMiddleImage3;
extern SDL_Surface *fireLeftMiddleImage4;

extern SDL_Surface *fireRightMiddleImage1;
extern SDL_Surface *fireRightMiddleImage2;
extern SDL_Surface *fireRightMiddleImage3;
extern SDL_Surface *fireRightMiddleImage4;

extern SDL_Surface *fireUpMiddleImage1;
extern SDL_Surface *fireUpMiddleImage2;
extern SDL_Surface *fireUpMiddleImage3;
extern SDL_Surface *fireUpMiddleImage4;

extern SDL_Surface *fireDownMiddleImage1;
extern SDL_Surface *fireDownMiddleImage2;
extern SDL_Surface *fireDownMiddleImage3;
extern SDL_Surface *fireDownMiddleImage4;

extern SDL_Surface *iconBombImage1;
extern SDL_Surface *iconBombImage2;

extern SDL_Surface *iconFireImage1;
extern SDL_Surface *iconFireImage2;

extern SDL_Surface *iconKeyImage1;
extern SDL_Surface *iconKeyImage2;

extern TTF_Font *font;
extern SDL_AudioSpec audioFmt;

struct audioSample {
    Uint8 *data;
    Uint32 dpos;
    Uint32 dlen;
};

extern audioSample sounds[NUM_SOUNDS];

void mixaudio(void *unused, Uint8 *stream, int len);
void playSound(string file, bool loop, int vol);
void repeatSound(bool loop);
void setSoundVolume(int vol);

void displayImage(SDL_Surface *image, int x, int y);
void displaySpriteImage(SDL_Surface *sprite, int x, int y, int dx, int dy, int sprite_size, int colorkey);
void drawText(string texto, SDL_Surface* dst, int x, int y, SDL_Color color);

#endif
