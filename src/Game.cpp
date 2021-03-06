#include "Game.h"   

Game::Game(){
    menuoption=0;
    close= false;
    list<int> pressing;
    first = 128;
    enabledsound=1;
}

void Game::newGame(){
    SDL_startup();
    loadImages();
    startGame();
    releaseImages();
    SDL_CloseAudio();
    TTF_Quit();
    SDL_Quit(); 
}


void Game::startGame(){
    while(!close){
        showMenu();
        if(!close){
            switch(menuoption){
                case 0:
                    if(enabledsound)
                       playSound("data/jingle_bells.wav", true, SDL_MIX_MAXVOLUME);
                    play();
                    break;
                case 1:
                    showOptions();
                    break;
                case 2:
                    showAbout();
                    break;
            }
        }
    }
}


void Game::showMenu(){
    menuoption=0;
    int sx,sy;
    sx=80;
    sy=190;
    color = {0, 0, 0};
    int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    bool choose = false;
    while(!choose && !close){
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
        displayImage(menuImage,0,0);
        drawText("Aperte B para selecionar", screen, 80, 390,color);
        handleMenuControl(sx, sy, close, choose);
        displayImage(icon, sx, sy);
        SDL_Flip(screen);
    }
}

void Game::handleMenuControl(int& sx, int& sy, bool& close, bool&choose){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        sy = sy - 65;
                        if(sy<190) sy = 320;  
                        break;
                    case SDLK_DOWN:
                        sy = sy + 65;
                        if(sy>320) sy = 190;
                        break;
                    case SDLK_b:
                        choose=true;
                        if(sy==320)
                            menuoption = 2;
                        else if(sy==255)
                            menuoption = 1;
                        else 
                            menuoption = 0;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                close=true;
                choose=true;
                break;
        }
    }
}

void Game::play(){
    map.loadMap("src/map.txt");
    player = new Player(0, 0, 0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE);
    enemy = new Enemy(9, 0, 1, 0, 0, ENEMY_SPRITE_SIZE);
    enemy2 = new Enemy(7, 6, 2, 0, ENEMY_SPRITE_SIZE, ENEMY_SPRITE_SIZE);
    enemy3 = new Enemy(5, 10, 3, 0, ENEMY_SPRITE_SIZE*2, ENEMY_SPRITE_SIZE);
    while(!close) {
        while(SDL_PollEvent(&event)) {
            switch(event.type){
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) 
                        pauseGame();
                    else 
                        pressing.push_back(event.key.keysym.sym);
                    //inserir na lista event.key.keysym.sym
                    break;
                case SDL_KEYUP:
                    pressing.remove(event.key.keysym.sym);
                    //remover da lista event.key.keysym.sym
                    break;
                case SDL_QUIT:
                    close = true;
                    break;
            }
        }
        player->handleControl(pressing);
        enemy->action();
        enemy2->action();
        enemy3->action();
        //threadplayer = SDL_CreateThread(callcontrol, NULL);
        //threadenemy1 = SDL_CreateThread(callAction, NULL);
        //threadenemy2 = SDL_CreateThread(callAction2, NULL);
        //threadenemy3 = SDL_CreateThread(callAction3, NULL);
        enemy->killPlayer();
        enemy2->killPlayer();
        enemy3->killPlayer();
        map.action();
        map.paint(player->life);
        map.moveAnimation();
        enemy->moveAnimation();
        enemy2->moveAnimation();
        enemy3->moveAnimation();
        player->moveAnimation();
        //threadtext = SDL_CreateThread(text, NULL);
        //showOnGameText
        SDL_Flip(screen);
        SDL_Delay(delay);
    }
}

int Game::callcontrol(void * unused){
   player->handleControl(pressing);
   //cout<<"Player executou"<<endl;
}

int Game::callAction(void * unused){
    enemy->action();
    //cout<<"Enemy 1 executou"<<endl;
}

int Game::callAction2(void * unused){
    enemy2->action();
    //cout<<"Enemy 2 executou"<<endl;
}

int Game::callAction3(void * unused){
    enemy3->action();
    //cout<<"Enemy 3 executou"<<endl;
}


int Game::showOnGameText(void * unused){
    color ={255,255,255};
    if(first){
        if(first>96)
            drawText("Direcionais movimentam o Bomberman...", screen, 120, 20,color);
        else if(first>64)
            drawText("aperte B para soltar Bomba...", screen, 120, 20,color);
        else if(first>32)
            drawText("ESC pausa o jogo.",screen, 120, 20,color);
        else
            drawText("Encontre a Chave!",screen, 200, 20,color);
        first--;
    }
    if(player->state==WIN){
        drawText("YOU WIN!", screen, 350, 15,color);
    }
    else if(player->state==LOSE){
        drawText("YOU LOSE!", screen, 350, 15,color);
    }
    else if(player->imuneTime && player->state!=DEAD){
        drawText("Imune por", screen, 350, 15,color);
        char * imuneTimestr = new char [32];
        drawText(to_string(player->imuneTime), screen, 430, 15,color);
    }
}

void Game::showOptions(){
    int sx,sy;
    sx=180;
    sy=190;
    color = {255, 255, 255};
    int colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    bool choose = false;
    SDL_Surface *optionsImage = IMG_Load("data/options.png");
    while(!choose && !close){
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
        displayImage(optionsImage,0,0);
        drawText("Aperte B para selecionar", screen, 180, 390,color);
        handleOptionsControl(sx, sy, close, choose);
        displayImage(icon, sx, sy);
        displaySpriteImage(item_sprite, sx,sy, GRID_SIZE, 3*GRID_SIZE, GRID_SIZE, colorkey);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(optionsImage);
}

void Game::handleOptionsControl(int& sx, int& sy, bool& close, bool& choose){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        sy=sy-65;
                        if(sy<190) sy=255;
                        break;
                    case SDLK_DOWN:
                        sy=(sy+65);
                        if(sy>255) sy=190;
                        break;
                    case SDLK_b:
                        enabledsound = (sy == 255);
                        choose=true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                close=true;
                choose=true;
                break;
        }
    }
}


void Game::showAbout(){
    bool done=false;
    color = {255, 255, 255};
    SDL_Surface *aboutImage = IMG_Load("data/about.png");
    while(!done){
        SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
        displayImage(aboutImage,0,0);
        drawText("Aperte B para voltar ao menu", screen, 180, 390,color);
        handleAboutControl(close, done);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(aboutImage);
}

void Game::handleAboutControl(bool& close, bool& done){
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
            case SDL_QUIT:
                done=true;
                close=true;
                break;
        }
    }
}

void Game::pauseGame(){
    color={255,255,255};
    bool choose=false;
    drawText("GAME PAUSED", screen, 200, 10,color);
    while(!choose && !close){
        handlePauseGameControl(choose, close);
        SDL_Flip(screen);
    }
}


void Game::handlePauseGameControl(bool& choose, bool& close){
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
            case SDL_QUIT:
                choose=true;
                close=true;
                break;
        }
    }
}

void Game::SDL_startup()
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
    SDL_WM_SetIcon(icon, NULL);
    if(TTF_Init() == -1) {
        printf("Unable to set font : %s\n", SDL_GetError());
        exit(1);
    }
    font = TTF_OpenFont("data/manaspc.ttf", 12);
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


void Game::loadImages()
{
    SDL_Surface * temp;

    menuImage =IMG_Load("data/bgmenu.png");
    mapImage = IMG_Load("data/bg.png");
    icon = IMG_Load("data/icon.png");

    temp  = SDL_LoadBMP("data/enemies_sprite.bmp");
    enemy_sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    temp  = SDL_LoadBMP("data/item_sprite.bmp");
    item_sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    temp  = SDL_LoadBMP("data/player_sprite.bmp");
    player_sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    temp  = SDL_LoadBMP("data/fire_sprite.bmp");
    fire_sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
}

void Game::releaseImages()
{
    SDL_FreeSurface(enemy_sprite);
    SDL_FreeSurface(item_sprite);
    SDL_FreeSurface(player_sprite);
    SDL_FreeSurface(fire_sprite);

    SDL_FreeSurface(menuImage);
    SDL_FreeSurface(mapImage);
}
