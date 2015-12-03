#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "Map.h"
#include "Character.h"

using namespace std;

class Game {
    private:
        void startGame();
        void showMenu();
        void play();
        int showOnGameText(void *);
        void showOptions();
        void showAbout();
        void pauseGame();
        void loadImages();
        void releaseImages();

        void SDL_startup();
        int callcontrol(void *);
        int callAction(void *);
        int callAction2(void *);
        int callAction3(void *);

        int menuoption;
        bool close;
        list<int> pressing;
        int first;
        int enabledsound;
    public:
        Game();
        void newGame();
};

#endif  




