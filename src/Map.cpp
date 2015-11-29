#include "global.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>


Map::Map(int width, int height) {
   map = new int[width*height];
   this->width = width;
   this->height = height;
}

void Map::loadMap(const char *fileName) {
    ifstream in(fileName);
    for(int i = 0; i<height; i++){
      for(int j = 0; j<width; j++){
         set(i,j, in.get() );
      }
      in.get();
      #ifdef __unix__
        in.get();
      #endif
    }
    in.close();
    createItemlist();
}

void Map::createItemlist(){
    createKey();
    createItem(BOMBPLUS, 1*GRID_SIZE, 4);
    createItem(FIREPOWER, 0*GRID_SIZE, 4);
}

void Map::createKey(){
    int a,b;
    srand ( time(NULL) );
    bool inserted=false;
    while(!inserted){
        a=rand()%MAX_X;
        b=rand()%MAX_Y;
        if(get(b,a)==ICE){
            itens.push_back(new Item(a,b,KEY, 0, 2*GRID_SIZE));
            inserted=true;
        }
    }
}

void Map::createItem(int itemType, int sprite_dy0, int quantity){
      int a,b;
      for(int i=0;i<quantity;i++){
        a=rand()%MAX_X;
        b=rand()%MAX_Y;
        if(get(b,a)!=SNOWMAN){
            itens.push_back(new Item(a,b,itemType, 0, sprite_dy0));
        }else{
            i--;
        }
    }
}

bool Map::passThrough(int lin,int col){
    return (get(lin,col)!=SNOWMAN && get(lin,col)!=ICE && get(lin,col)!=BOMB);
}

void Map::pickItem(int lin,int col, int item){
    list<Item*>::iterator temp;
    set(lin,col,EMPTY);
    for(list<Item*>::iterator it=itens.begin();it!=itens.end();it++){
        if((*(it))->x==col && (*(it))->y==lin && (*(it))->type==item){
            temp = it;
            it--;
            itens.erase(temp);
        }
    }
}

int Map::get(int lin, int col) {
   if(lin>=0 && lin<height && col>=0 && col<width)
       return map[lin*width + col];
   else return 0;
}

void Map::set(int lin, int col, int val) {
   if(lin>=0 && lin<height && col>=0 && col<width)
        map[lin*width + col] = val;
}

void Map::print(){
   for(int i = 0; i<height; i++){
      for(int j = 0; j<width; j++){
         cout << (char)get(i,j);
      }
      cout << endl;
   }
}

void Map::paint(int lives){
    displayImage(mapImage,0,0);
    int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    char * livestr=new char[GRID_SIZE];
    drawText(to_string(lives), screen, 80, 20,color);
     for(int i = 0; i<height; i++){
      for(int j = 0; j<width; j++){
          if(get(i,j) == ICE){
            displaySpriteImage(item_sprite, 48+(GRID_SIZE*j), 66+(GRID_SIZE*i), 0, 3*GRID_SIZE, GRID_SIZE, colorkey);
          }
        }
     }
}

void Map::moveAnimation(){
    for(list<Bomb*>::iterator it=bombs.begin();it!=bombs.end();it++){
        (*(it))->moveAnimation();
    }
    for(list<Item*>::iterator it=itens.begin();it!=itens.end();it++){
        (*(it))->moveAnimation();
    }
}

void Map::action(){
    list<Bomb*>::iterator temp;
    for(list<Bomb*>::iterator it=bombs.begin();it!=bombs.end();it++){
        (*(it))->action();
        if((*(it))->state==ASH){
            temp = it;
            it--;
            bombs.erase(temp);
        }
    }
    for(list<Item*>::iterator it=itens.begin();it!=itens.end();it++){
        (*(it))->action();
    }
}

