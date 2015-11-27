#include "Item.h"
#include "global.h"

Item :: Item(int x,int y, int type, int dx0, int dy0){
    this->type=type;
    this->x=x;
    this->y=y;
    this->dx0 = dx0;
    this->dy0 = dy0;
    this->colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    frame = 0;
    state = HIDE;
}

void Item :: action(){
    if(map.get(y,x)==EMPTY || state==SHOW){
        map.set(y,x,type);
        state=SHOW;
    }
}

void Item :: moveAnimation(){
    SDL_Surface * img1,*img2;
    int sx,sy;
    sx = 48+x*GRID_SIZE;
    sy = 66+y*GRID_SIZE;
    if(state==SHOW){
        frame = (frame+1)%4;
        dx0 = (frame*GRID_SIZE)%64;
        displaySpriteImage(item_sprite, sx, sy, dx0, dy0, GRID_SIZE, colorkey);
    }

}


