
#include "bomb.h"
#include "global.h"

Bomb::Bomb(int x, int y, int range)
{
    this->range=range;
    this->x = x;
    this->y = y;
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
            if(x+i<13){
                if(map.get(y,x+i)!=SNOWMAN && right){
                    if(map.get(y,x+i)==ICE)
                        right=0;
                    map.set(y,x+i,FIRE);
                }else{
                    right=0;
                }
            }if(y+i<11){
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
            if(x+i<13){
                if(map.get(y,x+i)==FIRE)
                    map.set(y,x+i,EMPTY);
            }if(y+i<11){
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
    if(state==SET){
        sx = 48+x*32;
        sy = 66+y*32;
    }else if(state==EXPLODE){
        sx = 48+x*32;
        sy = 66+y*32;
    }

    switch(state){
        case SET:
            //action();
            frame++;
            if(frame==5){
                frame=0;
            }
            break;
        case EXPLODE:
            frame++;
            if(frame==8){
                state = ASH;
            }
            break;
    }
    switch(frame){
        case 0:
            if(state==SET)
                displayImage(bombImage2, sx, sy);
            else if(state==EXPLODE){
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
            if(state==SET)
                displayImage(bombImage2, sx, sy);
            else if(state==EXPLODE){
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
            if(state==SET)
                displayImage(bombImage1, sx, sy);
            else if(state==EXPLODE){
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
            if(state==SET)
                displayImage(bombImage1, sx, sy);
            else if(state==EXPLODE){
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
            if(state==SET)
                displayImage(bombImage3, sx, sy);
            else if(state==EXPLODE){
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
            if(state==SET)
                displayImage(bombImage3, sx, sy);
            else if(state==EXPLODE){
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
    }
}
