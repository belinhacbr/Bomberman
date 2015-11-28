#include "Character.h"
#include "global.h"

Character :: Character(int x, int y, int dx0, int dy0, int sprite_size){
    this->x=x;
    this->y=y;
    this->dx0 = dx0;
    this->dy0 = dy0;
    this->sprite_size = sprite_size;
    this->colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
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

Player :: Player(int x, int y, int dx0, int dy0, int sprite_size) : Character(x, y, dx0, dy0, sprite_size){
    bombNumber=1;
    bombRange=1;
    life=3;
    imuneTime=0;
    deadTime=0;
    flic = false;
    colorkey = SDL_MapRGB(screen->format, 0, 255, 0);
}

void Player :: handleControl (list<int> &pressing) {
    if(state!=DEAD && state!=LOSE && state!=WIN){
        for(list<int>::iterator it=pressing.begin();it!=pressing.end();it++){
            switch(*(it)){
            case SDLK_DOWN:
                if((y+1)<MAX_Y && map.passThrough(y+1,x)){
                        if(state==0){
                            state = FRONT;
                        }
                    }
                break;
            case SDLK_RIGHT:
                if((x+1)<MAX_X && map.passThrough(y,x+1)){
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
        state=DEAD;
        imuneTime = IMUNE_TIME;
        deadTime = DEAD_TIME;
        life--;
        if(life==0){
            state=LOSE;
        }
    }
}

void Player :: moveAnimation(){
    SDL_Surface *img1, *img2, *img3;
    int sx = 48, sy = 52;
    switch(state){
        case STOP:
            dy0 = 2*sprite_size;
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE;
            break;
        case FRONT: //Front
            dy0 = 2*sprite_size;
            frame++;
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE + (frame*step);
            if(frame==4){
                state = 0;
                frame = 0;
                y++;
            }
            break;
        case LEFT:
            dy0 = 0;
            frame++;
            sx += x*GRID_SIZE - (frame*step);
            sy += y*GRID_SIZE;
            if(frame==4){
                state = 0;
                frame = 0;
                x--;
            }
            break;
        case BACK:
            dy0 = 3*sprite_size;
            frame++;
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE - (frame*step);
            if(frame==4){
                state = 0;
                frame = 0;
                y--;
            }
            break;
        case RIGHT:
            dy0 = 1*sprite_size;
            frame++;
            sx += x*GRID_SIZE + (frame*step);
            sy += y*GRID_SIZE ;
            if(frame==4){
                state = 0;
                frame = 0;
                x++;
            }
            break;
        case DEAD:
            dy0 = 4*sprite_size;
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE;
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
            dy0 = 6*sprite_size;
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE;
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
            dy0 = 5*sprite_size;
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE;
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
    if (frame >= 0 && (imuneTime%2)==0){
        dx0 = (frame%3)*sprite_size;
        displaySpriteImage(player_sprite, sx, sy, dx0, dy0, sprite_size, colorkey);
    }
}

Enemy :: Enemy(int x, int y, int routetype, int dx0=0, int dy0=0, int sprite_size=32) : Character(x, y, dx0, dy0, sprite_size){
    this->routetype=routetype;
    this->route=0;
}

void Enemy :: action (){
    if(state==STOP){
        switch(routetype){
            case 1:
                if(route){
                    if((y+1)<MAX_Y && map.passThrough(y+1,x) && map.get(y+1,x)!=FIRE) state = FRONT;
                    else if((x+1)<MAX_X && map.passThrough(y,x+1) && map.get(y,x+1)!=FIRE) state = RIGHT;
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
                    if((y+1)<MAX_Y && map.passThrough(y+1,x) && map.get(y+1,x)!=FIRE) state = FRONT;
                    else if((x+1)<MAX_X && map.passThrough(y,x+1) && map.get(y,x+1)!=FIRE) state = RIGHT;
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
                    if((y+1)<MAX_Y && map.passThrough(y+1,x) && map.get(y+1,x)!=FIRE) state = FRONT;
                    else if((x+1)<MAX_X && map.passThrough(y,x+1) && map.get(y,x+1)!=FIRE) state = RIGHT;
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
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE;
            break;
        case FRONT: //Front
            frame++;
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE + (frame*step);
            if(frame==4){
                state = 0;
                frame = 0;
                y++;
            }
            break;
        case LEFT:
            frame++;
            sx += x*GRID_SIZE - (frame*step);
            sy += y*GRID_SIZE;
            if(frame==4){
                state = 0;
                frame = 0;
                x--;
            }
            break;
        case BACK:
            //d = d - step;
            frame++;
            sx += x*GRID_SIZE;
            sy += y*GRID_SIZE - (frame*step);
            if(frame==4){
                state = 0;
                frame = 0;
                y--;
            }
            break;
        case RIGHT:
            frame++;
            sx += x*GRID_SIZE + (frame*step);
            sy += y*GRID_SIZE ;
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
    if (frame >= 0){
        dx0 = (frame%3)*sprite_size;
        displaySpriteImage(enemy_sprite, sx, sy, dx0, dy0, sprite_size, colorkey);
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
