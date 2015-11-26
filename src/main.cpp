//#include <windows.h>
#include <iostream>

#include "global.h"
#include "Map.h"
#include "Character.h"

using namespace std;

void menu();
void game();
int text(void *);
void options();
void about();
void gamePaused();
void loadImages();
void releaseImages();

int callcontrol(void *);
int callAction(void *);
int callAction2(void *);
int callAction3(void *);

void SDL_startup();
int menuoption=0;
bool close= false;
list<int> pressing;
int first = 128;
int enabledsound=1;

//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
int main (){
    SDL_startup();
    loadImages();

    while(!close){
        while(SDL_PollEvent(&event)) {
            menu();
            if(!close){
                switch(menuoption){
                    case 0:
                        if(enabledsound)
                           playSound("data/jingle_bells.wav", true, SDL_MIX_MAXVOLUME);
                        game();
                        break;
                    case 1:
                        options();
                        break;
                    case 2:
                        about();
                        break;
                }
            }
        }
    }
    releaseImages();
    SDL_CloseAudio();
    TTF_Quit();
    SDL_Quit(); //it finishes SDL initialisations
    return 0;
}

void menu(){
    menuoption=0;
    int sx,sy;
    sx=80;
    sy=115;
    cor = {0, 0, 0};
    bool choose = false;
    while(!choose){
        if(!close){
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
        displayImage(menuImage,0,0);
        desenha_texto("Aperte B para selecionar", screen, 80, 390,cor);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                            if(menuoption>0)
                                menuoption=(menuoption-1)%3;
                             break;
                        case SDLK_DOWN:
                            menuoption=(menuoption+1)%3;
                            break;
                        case SDLK_b:
                            choose=true;
                             break;
                        default:
                            break;
                    }
                break;
            }
        }
        if (event.type == SDL_QUIT) {
            close=true;
            choose=true;
        }
        switch(menuoption){
            case 0:
                sy=190;
                displayImage(iconImage,sx,sy);
                break;
            case 1:
                sy=255;
                displayImage(iconImage,sx,sy);
                break;
            case 2:
                sy=320;
                displayImage(iconImage,sx,sy);

                break;
        }
        SDL_Flip(screen);
        }
    }
}

void game(){
    map.loadMap("map.txt");
    player = new Player(0,0);
    enemy = new Enemy (9,0, enemyImage1, enemyImage2, enemyImage3,1);
    enemy2 = new Enemy (7,6, enemy2Image1, enemy2Image2, enemy2Image3,2);
    enemy3 = new Enemy (5,10, enemy3Image1, enemy3Image2, enemy3Image3,3);

    while(!close) {
        while(SDL_PollEvent(&event)) {
            switch(event.type){
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        gamePaused();
                    }
                    else{
                        pressing.push_back(event.key.keysym.sym);
                    }
                    //inserir na lista event.key.keysym.sym
                    break;
                case SDL_KEYUP:
                    pressing.remove(event.key.keysym.sym);
                    //remover da lista event.key.keysym.sym
                    break;
            }
            if (event.type == SDL_QUIT) {
                close=true;
            }
        }
        threadplayer = SDL_CreateThread(callcontrol, NULL);
        threadenemy1 = SDL_CreateThread(callAction, NULL);
        threadenemy2 = SDL_CreateThread(callAction2, NULL);
        threadenemy3 = SDL_CreateThread(callAction3, NULL);
        enemy->killPlayer();
        enemy2->killPlayer();
        enemy3->killPlayer();
        map.action();
        map.paint(mapImage,iceImage, player->life);
        map.moveAnimation();
        enemy->moveAnimation();
        enemy2->moveAnimation();
        enemy3->moveAnimation();
        player->moveAnimation();
        threadtext = SDL_CreateThread(text, NULL);
        SDL_Flip(screen);
        SDL_Delay(delay);
    }
}

int callcontrol(void * unused){
   player->handleControl(pressing);
   cout<<"Player executou"<<endl;
}

int callAction(void * unused){
    enemy->action();
    cout<<"Enemy 1 executou"<<endl;
}

int callAction2(void * unused){
    enemy2->action();
    cout<<"Enemy 2 executou"<<endl;
}

int callAction3(void * unused){
    enemy3->action();
    cout<<"Enemy 3 executou"<<endl;
}


int text(void * unused){
    cor ={255,255,255};
    if(first){
        if(first>96)
            desenha_texto("Direcionais movimentam o Bomberman...", screen, 120, 20,cor);
        else if(first>64)
            desenha_texto("aperte B para soltar Bomba...", screen, 120, 20,cor);
        else if(first>32)
            desenha_texto("ESC pausa o jogo.",screen, 120, 20,cor);
        else
            desenha_texto("Encontre a Chave!",screen, 200, 20,cor);
        first--;
    }
    if(player->state==WIN){
        desenha_texto("YOU WIN!", screen, 350, 15,cor);
    }
    else if(player->state==LOSE){
        desenha_texto("YOU LOSE!", screen, 350, 15,cor);
    }
    else if(player->imuneTime && player->state!=DEAD){
        desenha_texto("Imune por", screen, 350, 15,cor);
        char * imuneTimestr = new char [32];
        desenha_texto(itoa(player->imuneTime,imuneTimestr,10), screen, 430, 15,cor);
    }
}

void options(){
    int sx,sy;
    sx=180;
    sy=190;
    cor = {255, 255, 255};
    bool choose = false;
    SDL_Surface *optionsImage = IMG_Load("data/options.png");
    while(!choose){
        if(!close){
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
        displayImage(optionsImage,0,0);
        desenha_texto("Aperte B para selecionar", screen, 180, 390,cor);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                                enabledsound = 1;
                             break;
                        case SDLK_DOWN:
                                enabledsound = 0;
                            break;
                        case SDLK_b:
                            choose=true;
                             break;
                        default:
                            break;
                    }
                break;
            }
        }
        if (event.type == SDL_QUIT) {
            close=true;
            choose=true;
        }
        switch(enabledsound){
            case 0:
                sy=255;
                displayImage(iconImage,sx,sy);
                break;
            case 1:
                sy=190;
                displayImage(iconImage,sx,sy);
                break;
        }
        SDL_Flip(screen);
        }
    }
}

void about(){
    bool done=false;
    cor = {255, 255, 255};
    SDL_Surface *aboutImage = IMG_Load("data/about.png");
    while(!done){
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
        displayImage(aboutImage,0,0);
        desenha_texto("Aperte B para voltar ao menu", screen, 180, 390,cor);
        SDL_Flip(screen);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_b:
                            done=true;
                             break;
                        default:
                            break;
                    }
                break;
            }
            if (event.type == SDL_QUIT) {
                done=true;
                close=true;
            }
        }
    }
    SDL_FreeSurface(aboutImage);
}

void gamePaused(){
    cor={255,255,255};
    bool choose=false;
    desenha_texto("GAME PAUSED", screen, 200, 10,cor);
    while(!choose){
        if(!close){
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                            case SDLK_ESCAPE:
                                choose=true;
                                 break;
                            default:
                                break;
                        }
                    break;
                }
                if (event.type == SDL_QUIT) {
                    choose=true;
                    close=true;
                }
            }
            SDL_Flip(screen);
        }
    }

}

void SDL_startup()
{
    if( SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialise SDL: %s\n", SDL_GetError());
        exit(1);
    }

    //it's used to guarantee that the SDL_Quit function is called when the application exits;
    atexit(SDL_Quit);

    screen = SDL_SetVideoMode(515, 442, 16, SDL_SWSURFACE); //width, height, bitdepth

    if(screen==NULL){
        printf("Unable to set video mode: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_WM_SetCaption("Bomberman", "Bomberman"); //topTitle, iconTitle
    SDL_Surface* icon = IMG_Load("data/icon.png");
    SDL_WM_SetIcon(icon, NULL);
    if(TTF_Init() == -1) {
        printf("Unable to set font : %s\n", SDL_GetError());
        exit(1);
    }
    font = TTF_OpenFont("manaspc.ttf", 12);
    /* ajusta para áudio em  16-bit stereo com 22Khz */
    //audioFmt.freq = 22050;
    audioFmt.freq = SOUND_FREQUENCY;
    audioFmt.format = AUDIO_S16;
    audioFmt.channels = 1;//2
    audioFmt.samples = 1024;//512;        /* um bom valor para jogos */
    audioFmt.callback = mixaudio;
    audioFmt.userdata = NULL;
    if ( SDL_OpenAudio(&audioFmt, NULL) < 0 ) {
        fprintf(stderr, "Unable to open the audio: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_PauseAudio(0);

    SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );//parado
}


void loadImages()
{

    menuImage =IMG_Load("data/bgmenu.png");
    iconImage = IMG_Load("data/icon.png");

    mapImage = IMG_Load("data/bg.png");
    iceImage = IMG_Load("data/neve.png");

    frontImage1 = IMG_Load("data/Down.png");
    frontImage2 = IMG_Load("data/DownEsq.png");
    frontImage3 = IMG_Load("data/DownDir.png");

    rightImage1 = IMG_Load("data/Right.png");
    rightImage2 = IMG_Load("data/RightEsq.png");
    rightImage3 = IMG_Load("data/RightDir.png");

    backImage1 = IMG_Load("data/Up.png");
    backImage2 = IMG_Load("data/UpEsq.png");
    backImage3 = IMG_Load("data/UpDir.png");

    leftImage1 = IMG_Load("data/Left.png");
    leftImage2 = IMG_Load("data/LeftEsq.png");
    leftImage3 = IMG_Load("data/LeftDir.png");

    deadImage1 = IMG_Load("data/dead1.png");
    deadImage2 = IMG_Load("data/dead2.png");
    deadImage3 = IMG_Load("data/dead3.png");

    winImage1 = IMG_Load("data/win1.png");
    winImage2 = IMG_Load("data/win2.png");
    winImage3 = IMG_Load("data/win3.png");

    loseImage1 = IMG_Load("data/lose1.png");
    loseImage2 = IMG_Load("data/lose2.png");
    loseImage3 = IMG_Load("data/lose3.png");

    enemyImage1 = IMG_Load("data/penguin.png");
    enemyImage2 = IMG_Load("data/penguin0.png");
    enemyImage3 = IMG_Load("data/penguin1.png");

    enemy2Image1 = IMG_Load("data/tiny.png");
    enemy2Image2 = IMG_Load("data/tiny0.png");
    enemy2Image3 = IMG_Load("data/tiny1.png");

    enemy3Image1 = IMG_Load("data/jelly.png");
    enemy3Image2 = IMG_Load("data/jelly0.png");
    enemy3Image3 = IMG_Load("data/jelly1.png");

    bombImage1 = IMG_Load("data/bomb1.png");
    bombImage2 = IMG_Load("data/bomb2.png");
    bombImage3 = IMG_Load("data/bomb3.png");

    fireCenterImage1 = IMG_Load("data/firec1.png");
    fireCenterImage2 = IMG_Load("data/firec2.png");
    fireCenterImage3 = IMG_Load("data/firec3.png");
    fireCenterImage4 = IMG_Load("data/firec4.png");

    fireUpImage1 = IMG_Load("data/fireu1.png");
    fireUpImage2 = IMG_Load("data/fireu2.png");
    fireUpImage3 = IMG_Load("data/fireu3.png");
    fireUpImage4 = IMG_Load("data/fireu4.png");

    fireDownImage1 = IMG_Load("data/fired1.png");
    fireDownImage2 = IMG_Load("data/fired2.png");
    fireDownImage3 = IMG_Load("data/fired3.png");
    fireDownImage4 = IMG_Load("data/fired4.png");

    fireLeftImage1 = IMG_Load("data/firel1.png");
    fireLeftImage2 = IMG_Load("data/firel2.png");
    fireLeftImage3 = IMG_Load("data/firel3.png");
    fireLeftImage4 = IMG_Load("data/firel4.png");

    fireRightImage1 = IMG_Load("data/firer1.png");
    fireRightImage2 = IMG_Load("data/firer2.png");
    fireRightImage3 = IMG_Load("data/firer3.png");
    fireRightImage4 = IMG_Load("data/firer4.png");

    fireLeftMiddleImage1 = IMG_Load("data/firelm1.png");
    fireLeftMiddleImage2 = IMG_Load("data/firelm2.png");
    fireLeftMiddleImage3 = IMG_Load("data/firelm3.png");
    fireLeftMiddleImage4 = IMG_Load("data/firelm4.png");

    fireRightMiddleImage1 = IMG_Load("data/firerm1.png");
    fireRightMiddleImage2 = IMG_Load("data/firerm2.png");
    fireRightMiddleImage3 = IMG_Load("data/firerm3.png");
    fireRightMiddleImage4 = IMG_Load("data/firerm4.png");

    fireUpMiddleImage1 = IMG_Load("data/firem1.png");
    fireUpMiddleImage2 = IMG_Load("data/firem2.png");
    fireUpMiddleImage3 = IMG_Load("data/firem3.png");
    fireUpMiddleImage4 = IMG_Load("data/firem4.png");

    fireDownMiddleImage1 = IMG_Load("data/firem1.png");
    fireDownMiddleImage2 = IMG_Load("data/firem2.png");
    fireDownMiddleImage3 = IMG_Load("data/firem3.png");
    fireDownMiddleImage4 = IMG_Load("data/firem4.png");

    iconBombImage1 = IMG_Load("data/itembomb1.png");
    iconBombImage2 = IMG_Load("data/itembomb2.png");

    iconFireImage1 = IMG_Load("data/itemfire1.png");
    iconFireImage2 = IMG_Load("data/itemfire2.png");

    iconKeyImage1 = IMG_Load("data/key.png");
    iconKeyImage2 = IMG_Load("data/key2.png");
}

void releaseImages()
{
    SDL_FreeSurface(menuImage);
    SDL_FreeSurface(iconImage);

    SDL_FreeSurface(mapImage);//free memory
    SDL_FreeSurface(iceImage);//free memory

    SDL_FreeSurface(frontImage1);
    SDL_FreeSurface(frontImage2);
    SDL_FreeSurface(frontImage3);

    SDL_FreeSurface(rightImage1);
    SDL_FreeSurface(rightImage2);
    SDL_FreeSurface(rightImage3);

    SDL_FreeSurface(backImage1);
    SDL_FreeSurface(backImage2);
    SDL_FreeSurface(backImage3);

    SDL_FreeSurface(leftImage1);
    SDL_FreeSurface(leftImage2);
    SDL_FreeSurface(leftImage3);

    SDL_FreeSurface(enemyImage1);
    SDL_FreeSurface(enemyImage2);
    SDL_FreeSurface(enemyImage3);

    SDL_FreeSurface(enemy2Image1);
    SDL_FreeSurface(enemy2Image2);
    SDL_FreeSurface(enemy2Image3);

    SDL_FreeSurface(enemy3Image1);
    SDL_FreeSurface(enemy3Image2);
    SDL_FreeSurface(enemy3Image3);

    SDL_FreeSurface(fireCenterImage1);
    SDL_FreeSurface(fireCenterImage2);
    SDL_FreeSurface(fireCenterImage3);
    SDL_FreeSurface(fireCenterImage4);

    SDL_FreeSurface(fireUpImage1);
    SDL_FreeSurface(fireUpImage2);
    SDL_FreeSurface(fireUpImage3);
    SDL_FreeSurface(fireUpImage4);

    SDL_FreeSurface(fireDownImage1);
    SDL_FreeSurface(fireDownImage2);
    SDL_FreeSurface(fireDownImage3);
    SDL_FreeSurface(fireDownImage4);

    SDL_FreeSurface(fireLeftImage1);
    SDL_FreeSurface(fireLeftImage2);
    SDL_FreeSurface(fireLeftImage3);
    SDL_FreeSurface(fireLeftImage4);

    SDL_FreeSurface(fireRightImage1);
    SDL_FreeSurface(fireRightImage2);
    SDL_FreeSurface(fireRightImage3);
    SDL_FreeSurface(fireRightImage4);

    SDL_FreeSurface(fireLeftMiddleImage1);
    SDL_FreeSurface(fireLeftMiddleImage2);
    SDL_FreeSurface(fireLeftMiddleImage3);
    SDL_FreeSurface(fireLeftMiddleImage4);

    SDL_FreeSurface(fireRightMiddleImage1);
    SDL_FreeSurface(fireRightMiddleImage2);
    SDL_FreeSurface(fireRightMiddleImage3);
    SDL_FreeSurface(fireRightMiddleImage4);

    SDL_FreeSurface(fireUpMiddleImage1);
    SDL_FreeSurface(fireUpMiddleImage2);
    SDL_FreeSurface(fireUpMiddleImage3);
    SDL_FreeSurface(fireUpMiddleImage4);

    SDL_FreeSurface(fireDownMiddleImage1);
    SDL_FreeSurface(fireDownMiddleImage2);
    SDL_FreeSurface(fireDownMiddleImage3);
    SDL_FreeSurface(fireDownMiddleImage4);
}
