#include "item.h"
#include "global.h"

Item :: Item(int x,int y, int type){
    this->type=type;
    this->x=x;
    this->y=y;
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
    sx = 48+x*32;
    sy = 66+y*32;
    if(type==BOMBPLUS){
        img1=iconBombImage1;
        img2=iconBombImage2;
    }else if(type==FIREPOWER){
        img1=iconFireImage1;
        img2=iconFireImage2;
    }else if(type==KEY){
        img1=iconKeyImage1;
        img2=iconKeyImage2;
    }
    if(state==SHOW){
        frame=(frame+1)%4;
        switch(frame){
            case 0:
                displayImage(img1, sx, sy);
            break;
            case 1:
                displayImage(img1, sx, sy);
            break;
            case 2:
                displayImage(img2, sx, sy);
            break;
            case 3:
                displayImage(img2, sx, sy);
            break;
        }
    }

}


