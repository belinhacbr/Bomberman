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
     //in.get(); //LINUX
    }
    in.close();
    createItemlist();
}

void Map :: createItemlist(){
    int a,b;
    srand ( time(NULL) );
    bool inserted=false;
    while(!inserted){
        a=rand()%13;
        b=rand()%11;
        if(get(b,a)==ICE){
            itens.push_back(new Item(a,b,KEY));//gera chave
            inserted=true;
        }
    }
    for(int i=0;i<4;i++){//gera item de bomba
        a=rand()%13;
        b=rand()%11;
        if(get(b,a)!=SNOWMAN){
            itens.push_back(new Item(a,b,BOMBPLUS));
        }else{
            i--;
        }
    }
    for(int i=0;i<4;i++){//gera item de fogo
        a=rand()%13;
        b=rand()%11;
        if(get(b,a)!=SNOWMAN){
            itens.push_back(new Item(rand()%11,rand()%13,FIREPOWER));
        }else{
            i--;
        }
    }
}

bool Map :: passThrough(int lin,int col){
    return (get(lin,col)!=SNOWMAN && get(lin,col)!=ICE && get(lin,col)!=BOMB);
}

void Map :: pickItem(int lin,int col, int item){
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

void Map::paint(SDL_Surface * bg, SDL_Surface * ice,int live){
    displayImage(bg,0,0);
    char * livestr=new char[32];
    desenha_texto(itoa(live,livestr,10), screen, 80, 20,cor);
     for(int i = 0; i<height; i++){
      for(int j = 0; j<width; j++){
          if(get(i,j) == ICE){
            displayImage(ice, 48+(32*j), 66+(32*i));
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

