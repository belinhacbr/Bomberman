#include "Character.h"
#include "global.h"

Character :: Character(int x, int y){
    this->x=x;
    this->y=y;
    frame=0;
    state=0;
    life=1;
}

bool Character :: collide (Character *c){
    return ( c->x == this->x && c->y==this->y);
}

bool Character :: collide(int x, int y){
    return (x == this->x && y == this->y);
}

Player :: Player(int x, int y) : Character(x,y){
    bombNumber=1;
    bombRange=1;
    life=3;
    imuneTime=0;
    deadTime=0;
    flic = false;
}

void Player :: handleControl (list<int> &pressing) {
    if(state!=DEAD && state!=LOSE && state!=WIN){
        for(list<int>::iterator it=pressing.begin();it!=pressing.end();it++){
            switch(*(it)){
            case SDLK_DOWN:
                if((y+1)<11 && map.passThrough(y+1,x)){
                        if(state==0){
                            state = FRONT;
                        }
                    }
                break;
            case SDLK_RIGHT:
                if((x+1)<13 && map.passThrough(y,x+1)){
                        if(state==0){
                            state = RIGHT;
                        }
                    }
                break;
            case SDLK_LEFT:
                if((x-1)>=0 && map.passThrough(y,x-1)){
                        if(state==0){
                            state = LEFT;
                        }
                    }
                break;
            case SDLK_UP:
                if((y-1)>=0 && map.passThrough(y-1,x)){
                        if(state==0){
                            state = BACK;
                        }
                    }
                break;
            case SDLK_b:
                    if(bombNumber>map.bombs.size()){
                        if(map.get(y,x)!=BOMB){
                            map.set(y,x,BOMB);
                            map.bombs.push_back(new Bomb(x,y,bombRange));
                        }
                    }
                break;
            }
        }
        if(map.get(y,x)==FIRE){
            die();
        }
        else if(map.get(y,x)==FIREPOWER){
            map.pickItem(y,x,FIREPOWER);
            bombRange++;
        }
        else if(map.get(y,x)==BOMBPLUS){
            map.pickItem(y,x,BOMBPLUS);
            bombNumber++;
        }
        else if(map.get(y,x)==KEY){
            map.pickItem(y,x,KEY);
            state = WIN;
        }

    }
    if(state!=LOSE){
        if(deadTime){
            deadTime--;
            if(deadTime==0){
                state = STOP;
                frame = 0;
            }
        }else if(imuneTime){
            imuneTime--;
        }
    }
}


void Player :: die(){
    if(imuneTime==0){
        //cout<<"arghh!"<<endl;
        state=DEAD;
        imuneTime = IMUNE_TIME;
        deadTime = DEAD_TIME;
        life--;
        if(life==0){
            state=LOSE;
            //cout<<"GAME OVER!"<<endl;
        }
    }
}

void Player :: moveAnimation(){
    SDL_Surface *img1, *img2, *img3;
    int sx = 48, sy = 52;
    switch(state){
        case STOP:
            img2 = frontImage1;
            sx += x*32;
            sy += y*32;
            break;
        case FRONT: //Front
            sx += x*32;
            sy += y*32 + (frame+1)*step;
            img1 = frontImage1;
            img2 = frontImage2;
            img3 = frontImage3;
            frame++;
            if(frame==4){
                state = 0;
                frame = 0;
                y++;
            }
            break;
        case LEFT:
            sx += x*32 - (frame+1)*step;
            sy += y*32;
            img1 = leftImage1;
            img2 = leftImage2;
            img3 = leftImage3;

            frame++;
            if(frame==4){
                state = 0;
                frame = 0;
                x--;
            }
            break;
        case BACK:
            sx += x*32;
            sy += y*32 - (frame+1)*step;
            img1 = backImage1;
            img2 = backImage2;
            img3 = backImage3;
            frame++;
            if(frame==4){
                state = 0;
                frame = 0;
                y--;
            }
            break;
        case RIGHT:
            sx += x*32 + (frame+1)*step;
            sy += y*32 ;
            img1 = rightImage1;
            img2 = rightImage2;
            img3 = rightImage3;
            frame++;
            if(frame==4){
                state = 0;
                frame = 0;
                x++;
            }
            break;
        case DEAD:
            sx += x*32;
            sy += y*32;
            img1=deadImage2;
            img2=deadImage1;
            img3=deadImage3;
            if(flic){
                flic=0;
                frame ++;
            }else
                flic=1;
            if(frame==3){
                frame = -1;
            }
            break;
        case WIN:
            sx += x*32;
            sy += y*32;
            img1=winImage1;
            img2=winImage2;
            img3=winImage3;
            if(flic){
                flic=0;
                frame ++;
            }else
                flic=1;
            if(frame==4){
                frame = 0;
            }
            break;
        case LOSE:
            sx += x*32;
            sy += y*32;
            img1=loseImage1;
            img2=loseImage2;
            img3=loseImage3;
            if(flic){
                flic=0;
                frame ++;
            }else
                flic=1;
            if(frame==4){
                frame = 0;
            }
            break;
    }

    switch(frame){
        case 0:
            displayImage(img2, sx, sy);
            break;
        case 1:
            displayImage(img1, sx, sy);
            break;
        case 2:
            displayImage(img3, sx, sy);
            break;
        case 3:
            displayImage(img1, sx, sy);
            break;
    }

    /*if(state==WIN){
        cor={255,255,255};
        drawText("YOU WIN!", screen, 300, 15,cor);
    }
    else if(state==LOSE){
        cor={255,255,255};
        drawText("YOU LOSE!", screen, 300, 15,cor);
    }
    else if(imuneTime && state!=DEAD){
        cor={255,255,255};
        drawText("Imune por", screen, 300, 15,cor);
        char * imuneTimestr = new char [32];
        drawText(itoa(imuneTime,imuneTimestr,10), screen, 380, 15,cor);
    }*/
}

Enemy :: Enemy(int x, int y, SDL_Surface * img1, SDL_Surface *img2, SDL_Surface * img3, int routetype) : Character(x,y){
    this->img1=img1;
    this->img2=img2;
    this->img3=img3;
    this->routetype=routetype;
    route=0;
}

void Enemy :: action (){
    if(state==STOP){
        switch(routetype){
            case 1:
                if(route){
                    if((y+1)<11 && map.passThrough(y+1,x) && map.get(y+1,x)!=FIRE) state = FRONT;
                    else if((x+1)<13 && map.passThrough(y,x+1) && map.get(y,x+1)!=FIRE) state = RIGHT;
                    else route = 0;
                }
                else{
                    if((x-1)>=0 && map.passThrough(y,x-1) && map.get(y,x-1)!=FIRE) state = LEFT;
                    else if((y-1)>=0 && map.passThrough(y-1,x) && map.get(y-1,x)!=FIRE) state = BACK;
                    else route = 1;
                }
            break;
            case 2:
                if(route){
                    if((y+1)<11 && map.passThrough(y+1,x) && map.get(y+1,x)!=FIRE) state = FRONT;
                    else if((x+1)<13 && map.passThrough(y,x+1) && map.get(y,x+1)!=FIRE) state = RIGHT;
                    else route = 0;
                }
                else{
                    if((x-1)>=0 && map.passThrough(y,x-1) && map.get(y,x-1)!=FIRE) state = LEFT;
                    else if((y-1)>=0 && map.passThrough(y-1,x) && map.get(y-1,x)!=FIRE) state = BACK;
                    else route = 1;
                }

            break;
            case 3:
                 if(route){
                    if((y+1)<11 && map.passThrough(y+1,x) && map.get(y+1,x)!=FIRE) state = FRONT;
                    else if((x+1)<13 && map.passThrough(y,x+1) && map.get(y,x+1)!=FIRE) state = RIGHT;
                    else route = 0;
                }
                else{
                    if((x-1)>=0 && map.passThrough(y,x-1) && map.get(y,x-1)!=FIRE) state = LEFT;
                    else if((y-1)>=0 && map.passThrough(y-1,x) && map.get(y-1,x)!=FIRE) state = BACK;
                    else route = 1;
                }
            break;
        }
    }
    if(map.get(y,x)==FIRE){
        die();
    }
}



void Enemy :: moveAnimation(){
    int sx = 48, sy = 66;
    switch(state){
        case STOP:
            sx += x*32;
            sy += y*32;
            break;
        case FRONT: //Front
            sx += x*32;
            sy += y*32 + (frame+1)*step;
            frame++;
            if(frame==4){
                state = 0;
                frame = 0;
                y++;
            }
            break;
        case LEFT:
            sx += x*32 - (frame+1)*step;
            sy += y*32;
            frame++;
            if(frame==4){
                state = 0;
                frame = 0;
                x--;
            }
            break;
        case BACK:
            //d = d - step;
            sx += x*32;
            sy += y*32 - (frame+1)*step;
            frame++;
            if(frame==4){
                state = 0;
                frame = 0;
                y--;
            }
            break;
        case RIGHT:
            sx += x*32 + (frame+1)*step;
            sy += y*32 ;
            frame++;
            if(frame==4){
                state = 0;
                frame = 0;
                x++;
            }
            break;
        case DEAD:
            frame = -1;
            break;
    }

    switch(frame){
        case 0:
            displayImage(img2, sx, sy);
            break;
        case 1:
            displayImage(img1, sx, sy);
            break;
        case 2:
            displayImage(img3, sx, sy);
            break;
        case 3:
            displayImage(img1, sx, sy);
            break;
    }
}

void Enemy :: die(){
    life--;
    if(life==0)
        state=DEAD;
}

void Enemy :: killPlayer(){
    if(collide(player) && player->state!=DEAD && state!=DEAD){
        player->die();
        //letreborn(); deixar espaço pro player renascer
    }
}
