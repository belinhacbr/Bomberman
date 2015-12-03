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
#define PLAYER_SPRITE_SIZE  48
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
extern SDL_Surface *mapImage;
extern SDL_Surface *icon;

extern SDL_Surface *item_sprite;
extern SDL_Surface *enemy_sprite;
extern SDL_Surface *fire_sprite;
extern SDL_Surface *player_sprite;

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
