
#include "Bomb.h"
#include "global.h"

Bomb::Bomb(int x, int y, int range){
    this->range=range;
    this->x = x;
    this->y = y;
    this->colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    this->state=SET;
    this->frame=0;
    this->timer=32;
    this->up=1,this->down=1,this->right=1,this->left=1;
}

void Bomb::action(){
    if(state==SET){
        timer--;
        if(timer==0){
            state=EXPLODE;
        }
    }else if(state==EXPLODE){
        for(int i = 0; i<=range; i++){
            if(x+i<MAX_X){
                if(map.get(y,x+i)!=SNOWMAN && right){
                    if(map.get(y,x+i)==ICE)
                        right=0;
                    map.set(y,x+i,FIRE);
                }else{
                    right=0;
                }
            }if(y+i<MAX_Y){
                if(map.get(y+i,x)!=SNOWMAN && up){
                    if(map.get(y+i,x)==ICE)
                        up=0;
                    map.set(y+i,x,FIRE);
                }
                else{
                    up=0;
                }
            }if(x-i>=0){
                if(map.get(y,x-i)!=SNOWMAN && left){
                    if(map.get(y,x-i)==ICE)
                        left=0;
                    map.set(y,x-i,FIRE);
                }
                else{
                    left=0;
                }
            }if(y-i>=0){
                if(map.get(y-i,x)!=SNOWMAN && down){
                    if(map.get(y-i,x)==ICE)
                        down=0;
                    map.set(y-i,x,FIRE);
                }
                else{
                    down=0;
                }
            }
       }
    }else if(state==ASH){
        for(int i = 0; i<=range; i++){
            if(x+i<MAX_X) 
                vanishBomb(x+i, y);
            if(y+i<MAX_Y) 
                vanishBomb(x, y+i);
            if(x-i>=0) 
                vanishBomb(x-i, y);
            if(y-i>=0)
                vanishBomb(x, y-i);
       }
    }
}

void Bomb::vanishBomb(int x, int y){
    if(map.get(y,x)==FIRE) map.set(y,x,EMPTY);
}

void Bomb::moveAnimation(){
    int sx, sy;
    sx = 48+x*GRID_SIZE;
    sy = 66+y*GRID_SIZE;
    switch(state){
        case SET:
            displayBomb(sx, sy);
            break;
        case EXPLODE:
            frame++;
            if(frame==8){
                state = ASH;
            }else{
                displayExplosion(sx, sy);
            }
            break;
    }

}

void Bomb::displayFire(int x, int y, int sx, int sy, int dx0, int dy0){
    if(map.get(y,x)==FIRE) displaySpriteImage(fire_sprite, sx, sy, dx0, dy0, GRID_SIZE, colorkey);
}

void Bomb::displayBomb(int sx, int sy){
    frame = (frame+1)%6;
    int dx0 = frame/2*GRID_SIZE;
    int dy0 = 3*GRID_SIZE;
    displaySpriteImage(enemy_sprite, sx, sy, dx0, dy0, GRID_SIZE, colorkey);
}

void Bomb::displayExplosion(int sx, int sy){
    int dx0, dy0;
    dx0 = frame/2*GRID_SIZE;
    displayFire(x, y, sx, sy, dx0, 3*GRID_SIZE);
    if(x-range>=0) //Left
        displayFire(x-range, y, sx-range*GRID_SIZE, sy, dx0, 5*GRID_SIZE);
    for(int i = 1; i<range; i++){
        if((x-i)>=0) //Left middle
            displayFire(x-i, y, sx-i*GRID_SIZE, sy, dx0, 1*GRID_SIZE);
    }
    if(y-range>=0) //Up
        displayFire(x, y-range, sx, sy-range*GRID_SIZE, dx0, 0);

    for(int i = 1; i<range; i++){
        if((y-i)>=0) //Up Middle
            displayFire(x, y-i, sx, sy-i*GRID_SIZE, dx0, 4*GRID_SIZE);
    }
    if(x+range<MAX_X) //Right
        displayFire(x+range, y, sx+range*GRID_SIZE, sy, dx0, 6*GRID_SIZE);

    for(int i = 1; i<range; i++){
        if((x+i)<MAX_X) //Right Middle
            displayFire(x+i, y, sx+i*GRID_SIZE, sy, dx0, 2*GRID_SIZE);
    }
    if(y+range<MAX_Y){ //Down
        displayFire(x, y+range, sx, sy+range*GRID_SIZE, dx0, 7*GRID_SIZE);
    }
    for(int i = 1; i<range; i++){
        if((y+i)<MAX_Y) //Down Middle
            displayFire(x, y+i, sx, sy+i*GRID_SIZE, dx0, 4*GRID_SIZE);
    }
}
