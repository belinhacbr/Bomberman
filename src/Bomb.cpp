
#include "Bomb.h"
#include "global.h"

Bomb::Bomb(int x, int y, int range)
{
    this->range=range;
    this->x = x;
    this->y = y;
    this->colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    state=SET;
    frame=0;
    timer=32;
    up=1,down=1,right=1,left=1;
}

void Bomb :: action(){
    if(state==SET){
        timer--;
        /*if(map.get(x,y)==FIRE)
            timer=0;*/
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
            if(x+i<MAX_X){
                if(map.get(y,x+i)==FIRE)
                    map.set(y,x+i,EMPTY);
            }if(y+i<MAX_Y){
                if(map.get(y+i,x)==FIRE)
                    map.set(y+i,x,EMPTY);
            }if(x-i>=0){
                if(map.get(y,x-i)==FIRE)
                    map.set(y,x-i,EMPTY);
            }if(y-i>=0){
                if(map.get(y-i,x)==FIRE)
                    map.set(y-i,x,EMPTY);
            }
       }
    }

}

void Bomb :: moveAnimation(){
    int sx, sy;
    int dx0, dy0;
    if(state==SET){
        sx = 48+x*GRID_SIZE;
        sy = 66+y*GRID_SIZE;
    }else if(state==EXPLODE){
        sx = 48+x*GRID_SIZE;
        sy = 66+y*GRID_SIZE;
    }
    switch(state){
        case SET:
            frame = (frame+1)%6;
            dx0 = frame/2*GRID_SIZE;
            dy0 = 3*GRID_SIZE;
            displaySpriteImage(enemy_sprite, sx, sy, dx0, dy0, GRID_SIZE, colorkey);
            break;
        case EXPLODE:
            frame++;
            if(frame==8){
                state = ASH;
            }else{
                dx0 = frame/2*GRID_SIZE;
                displaySpriteImage(fire_sprite, sx, sy, dx0, 3*GRID_SIZE, GRID_SIZE, colorkey);
                if(x-range>=0 && map.get(y,x-range)==FIRE){ //Left
                    displaySpriteImage(fire_sprite, sx-range*GRID_SIZE, sy, dx0, 5*GRID_SIZE, GRID_SIZE, colorkey);
                }
                for(int i = 1; i<range; i++){
                    if((x-i)>=0 && map.get(y,x-i)==FIRE){ //Left middle
                        displaySpriteImage(fire_sprite, sx-i*GRID_SIZE, sy, dx0, 1*GRID_SIZE, GRID_SIZE, colorkey);
                    }
                }
                if(y-range>=0 && map.get(y-range,x)==FIRE){ //Up
                    displaySpriteImage(fire_sprite, sx, sy-range*GRID_SIZE, dx0, 0, GRID_SIZE, colorkey);
                }
                for(int i = 1; i<range; i++){
                    if((y-i)>=0 && map.get(y-i,x)==FIRE){ //Up Middle
                        displaySpriteImage(fire_sprite, sx, sy-i*GRID_SIZE, dx0, 4*GRID_SIZE, GRID_SIZE, colorkey);
                    }
                }
                if(x+range<MAX_X && map.get(y,x+range)==FIRE){ //Right
                    displaySpriteImage(fire_sprite, sx+range*GRID_SIZE, sy, dx0, 6*GRID_SIZE, GRID_SIZE, colorkey);
                }
                for(int i = 1; i<range; i++){
                    if((x+i)<MAX_X && map.get(y,x+i)==FIRE){ //Right Middle
                        displaySpriteImage(fire_sprite, sx+i*GRID_SIZE, sy, dx0, 2*GRID_SIZE, GRID_SIZE, colorkey);
                    }
                }
                if(y+range<MAX_Y && map.get(y+range,x)==FIRE){ //Down
                    displaySpriteImage(fire_sprite, sx, sy+range*GRID_SIZE, dx0, 7*GRID_SIZE, GRID_SIZE, colorkey);
                }
                for(int i = 1; i<range; i++){
                    if((y+i)<MAX_Y && map.get(y+i,x)==FIRE){ //Down Middle
                        displaySpriteImage(fire_sprite, sx, sy+i*GRID_SIZE, dx0, 4*GRID_SIZE, GRID_SIZE, colorkey);
                    }
                }
            }
            break;
    }

}
