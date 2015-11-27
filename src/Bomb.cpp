
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
            //action();
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
                displayImage(fire_sprite, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE){ //Left
                    displayImage(fire_sprite, sx-range*GRID_SIZE, sy);
                }
                for(int i = 1; i<range; i++){
                    if((x-i)>=0 && map.get(y,x-i)==FIRE){ //Left middle
                        displayImage(fire_sprite, sx-i*GRID_SIZE, sy);
                    }
                }
                if(y-range>=0 && map.get(y-range,x)==FIRE){ //Up
                    displayImage(fire_sprite, sx, sy-range*GRID_SIZE);
                }
                for(int i = 1; i<range; i++){
                    if((y-i)>=0 && map.get(y-i,x)==FIRE){ //Up Middle
                        displayImage(fire_sprite, sx, sy-i*GRID_SIZE);
                    }
                }
                if(x+range<MAX_X && map.get(y,x+range)==FIRE){ //Right
                    displayImage(fire_sprite, sx+range*GRID_SIZE, sy);
                }
                for(int i = 1; i<range; i++){
                    if((x+i)<MAX_X && map.get(y,x+i)==FIRE){ //Right Middle
                        displayImage(fire_sprite, sx+i*GRID_SIZE, sy);
                    }
                }
                if(y+range<MAX_Y && map.get(y+range,x)==FIRE){ //Down
                    displayImage(fire_sprite, sx, sy+range*GRID_SIZE);
                }
                for(int i = 1; i<range; i++){
                    if((y+i)<MAX_Y && map.get(y+i,x)==FIRE){ //Down Middle
                        displayImage(fire_sprite, sx, sy+i*GRID_SIZE);
                    }
                }
            }
            break;
    }
    /*switch(frame){
        case 0:
            if(state==SET){
                //displaySpriteImage(enemy_sprite, sx, sy, dx0*sprite_size, dy0, sprite_size, colorkey);
            }else if(state==EXPLODE){
                displayImage(fireCenterImage1, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE)
                    displayImage(fireLeftImage1, sx-range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x-i)>=0 && map.get(y,x-i)==FIRE)
                        displayImage(fireLeftMiddleImage1, sx-i*32, sy);
                if(y-range>=0 && map.get(y-range,x)==FIRE)
                    displayImage(fireUpImage1, sx, sy-range*32);
                for(int i = 1; i<range; i++)
                    if((y-i)>=0 && map.get(y-i,x)==FIRE)
                        displayImage(fireUpMiddleImage1, sx, sy-i*32);
                if(x+range<13 && map.get(y,x+range)==FIRE)
                    displayImage(fireRightImage1, sx+range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x+i)<13 && map.get(y,x+i)==FIRE)
                        displayImage(fireRightMiddleImage1, sx+i*32, sy);
                if(y+range<11 && map.get(y+range,x)==FIRE)
                    displayImage(fireDownImage1, sx, sy+range*32);
                for(int i = 1; i<range; i++)
                    if((y+i)<11 && map.get(y+i,x)==FIRE)
                        displayImage(fireDownMiddleImage1, sx, sy+i*32);
            }
            break;
        case 1:
            if(state==SET){
                //displaySpriteImage(enemy_sprite, sx, sy, dx0*sprite_size, dy0, sprite_size, colorkey);
            }else if(state==EXPLODE){
                displayImage(fireCenterImage2, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE)
                    displayImage(fireLeftImage2, sx-range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x-i)>=0 && map.get(y,x-i)==FIRE)
                        displayImage(fireLeftMiddleImage2, sx-i*32, sy);
                if(y-range>=0 && map.get(y-range,x)==FIRE)
                    displayImage(fireUpImage2, sx, sy-range*32);
                for(int i = 1; i<range; i++)
                    if((y-i)>=0 && map.get(y-i,x)==FIRE)
                        displayImage(fireUpMiddleImage2, sx, sy-i*32);
                if(x+range<13 && map.get(y,x+range)==FIRE)
                    displayImage(fireRightImage2, sx+range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x+i)<13 && map.get(y,x+i)==FIRE)
                        displayImage(fireRightMiddleImage2, sx+i*32, sy);
                if(y+range<11 && map.get(y+range,x)==FIRE)
                    displayImage(fireDownImage2, sx, sy+range*32);
                for(int i = 1; i<range; i++)
                    if((y+i)<11 && map.get(y+i,x)==FIRE)
                        displayImage(fireDownMiddleImage2, sx, sy+i*32);
            }
            break;
        case 2:
            if(state==SET){
                //displaySpriteImage(enemy_sprite, sx, sy, dx0*sprite_size, dy0, sprite_size, colorkey);
            }else if(state==EXPLODE){
                displayImage(fireCenterImage3, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE)
                    displayImage(fireLeftImage3, sx-range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x-i)>=0 && map.get(y,x-i)==FIRE)
                        displayImage(fireLeftMiddleImage3, sx-i*32, sy);
                if(y-range>=0 && map.get(y-range,x)==FIRE)
                    displayImage(fireUpImage3, sx, sy-range*32);
                for(int i = 1; i<range; i++)
                    if((y-i)>=0 && map.get(y-i,x)==FIRE)
                        displayImage(fireUpMiddleImage3, sx, sy-i*32);
                if(x+range<13 && map.get(y,x+range)==FIRE)
                    displayImage(fireRightImage3, sx+range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x+i)<13 && map.get(y,x+i)==FIRE)
                        displayImage(fireRightMiddleImage3, sx+i*32, sy);
                if(y+range<11 && map.get(y+range,x)==FIRE)
                    displayImage(fireDownImage3, sx, sy+range*32);
                for(int i = 1; i<range; i++)
                    if((y+i)<11 && map.get(y+i,x)==FIRE)
                        displayImage(fireDownMiddleImage3, sx, sy+i*32);
            }
            break;
        case 3:
            if(state==SET){
                //displaySpriteImage(enemy_sprite, sx, sy, dx0*sprite_size, dy0, sprite_size, colorkey);
            }else if(state==EXPLODE){
               displayImage(fireCenterImage4, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE)
                    displayImage(fireLeftImage4, sx-range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x-i)>=0 && map.get(y,x-i)==FIRE)
                        displayImage(fireLeftMiddleImage4, sx-i*32, sy);
                if(y-range>=0 && map.get(y-range,x)==FIRE)
                    displayImage(fireUpImage4, sx, sy-range*32);
                for(int i = 1; i<range; i++)
                    if((y-i)>=0 && map.get(y-i,x)==FIRE)
                        displayImage(fireUpMiddleImage4, sx, sy-i*32);
                if(x+range<13 && map.get(y,x+range)==FIRE)
                    displayImage(fireRightImage4, sx+range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x+i)<13 && map.get(y,x+i)==FIRE)
                        displayImage(fireRightMiddleImage4, sx+i*32, sy);
                if(y+range<11 && map.get(y+range,x)==FIRE)
                    displayImage(fireDownImage4, sx, sy+range*32);
                for(int i = 1; i<range; i++)
                    if((y+i)<11 && map.get(y+i,x)==FIRE)
                        displayImage(fireDownMiddleImage4, sx, sy+i*32);
            }
            break;
        case 4:
            if(state==SET){
                //displaySpriteImage(enemy_sprite, sx, sy, dx0*sprite_size, dy0, sprite_size, colorkey);
            }else if(state==EXPLODE){
               displayImage(fireCenterImage4, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE)
                    displayImage(fireLeftImage4, sx-range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x-i)>=0 && map.get(y,x-i)==FIRE)
                        displayImage(fireLeftMiddleImage4, sx-i*32, sy);
                if(y-range>=0 && map.get(y-range,x)==FIRE)
                    displayImage(fireUpImage4, sx, sy-range*32);
                for(int i = 1; i<range; i++)
                    if((y-i)>=0 && map.get(y-i,x)==FIRE)
                        displayImage(fireUpMiddleImage4, sx, sy-i*32);
                if(x+range<13 && map.get(y,x+range)==FIRE)
                    displayImage(fireRightImage4, sx+range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x+i)<13 && map.get(y,x+i)==FIRE)
                        displayImage(fireRightMiddleImage4, sx+i*32, sy);
                if(y+range<11 && map.get(y+range,x)==FIRE)
                    displayImage(fireDownImage4, sx, sy+range*32);
                for(int i = 1; i<range; i++)
                    if((y+i)<11 && map.get(y+i,x)==FIRE)
                        displayImage(fireDownMiddleImage4, sx, sy+i*32);
            }
            break;
        case 5:
            if(state==SET){
                //displaySpriteImage(enemy_sprite, sx, sy, dx0*sprite_size, dy0, sprite_size, colorkey);
            }else if(state==EXPLODE){
                displayImage(fireCenterImage3, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE)
                    displayImage(fireLeftImage3, sx-range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x-i)>=0 && map.get(y,x-i)==FIRE)
                        displayImage(fireLeftMiddleImage3, sx-i*32, sy);
                if(y-range>=0 && map.get(y-range,x)==FIRE)
                    displayImage(fireUpImage3, sx, sy-range*32);
                for(int i = 1; i<range; i++)
                    if((y-i)>=0 && map.get(y-i,x)==FIRE)
                        displayImage(fireUpMiddleImage3, sx, sy-i*32);
                if(x+range<13 && map.get(y,x+range)==FIRE)
                    displayImage(fireRightImage3, sx+range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x+i)<13 && map.get(y,x+i)==FIRE)
                        displayImage(fireRightMiddleImage3, sx+i*32, sy);
                if(y+range<11 && map.get(y+range,x)==FIRE)
                    displayImage(fireDownImage3, sx, sy+range*32);
                for(int i = 1; i<range; i++)
                    if((y+i)<11 && map.get(y+i,x)==FIRE)
                        displayImage(fireDownMiddleImage3, sx, sy+i*32);
            }
            break;
        case 6:
            if(state==EXPLODE){
                displayImage(fireCenterImage2, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE)
                    displayImage(fireLeftImage2, sx-range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x-i)>=0 && map.get(y,x-i)==FIRE)
                        displayImage(fireLeftMiddleImage2, sx-i*32, sy);
                if(y-range>=0 && map.get(y-range,x)==FIRE)
                    displayImage(fireUpImage2, sx, sy-range*32);
                for(int i = 1; i<range; i++)
                    if((y-i)>=0 && map.get(y-i,x)==FIRE)
                        displayImage(fireUpMiddleImage2, sx, sy-i*32);
                if(x+range<13 && map.get(y,x+range)==FIRE)
                    displayImage(fireRightImage2, sx+range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x+i)<13 && map.get(y,x+i)==FIRE)
                        displayImage(fireRightMiddleImage2, sx+i*32, sy);
                if(y+range<11 && map.get(y+range,x)==FIRE)
                    displayImage(fireDownImage2, sx, sy+range*32);
                for(int i = 1; i<range; i++)
                    if((y+i)<11 && map.get(y+i,x)==FIRE)
                        displayImage(fireDownMiddleImage2, sx, sy+i*32);
            }
            break;
        case 7:
            if(state==EXPLODE){
                 displayImage(fireCenterImage1, sx, sy);
                if(x-range>=0 && map.get(y,x-range)==FIRE)
                    displayImage(fireLeftImage1, sx-range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x-i)>=0 && map.get(y,x-i)==FIRE)
                        displayImage(fireLeftMiddleImage1, sx-i*32, sy);
                if(y-range>=0 && map.get(y-range,x)==FIRE)
                    displayImage(fireUpImage1, sx, sy-range*32);
                for(int i = 1; i<range; i++)
                    if((y-i)>=0 && map.get(y-i,x)==FIRE)
                        displayImage(fireUpMiddleImage1, sx, sy-i*32);
                if(x+range<13 && map.get(y,x+range)==FIRE)
                    displayImage(fireRightImage1, sx+range*32, sy);
                for(int i = 1; i<range; i++)
                    if((x+i)<13 && map.get(y,x+i)==FIRE)
                        displayImage(fireRightMiddleImage1, sx+i*32, sy);
                if(y+range<11 && map.get(y+range,x)==FIRE)
                    displayImage(fireDownImage1, sx, sy+range*32);
                for(int i = 1; i<range; i++)
                    if((y+i)<11 && map.get(y+i,x)==FIRE)
                        displayImage(fireDownMiddleImage1, sx, sy+i*32);
            }
            break;
    }*/
}
