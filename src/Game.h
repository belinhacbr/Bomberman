#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "Map.h"
#include "Character.h"

using namespace std;

class Game {
    private:
        void startGame();
        void play();
        int showOnGameText(void *);

        void showMenu();
        void handleMenuControl(int&, int&, bool&, bool&);
        void showOptions();
        void handleOptionsControl(int&, int&, bool&, bool&);
        void showAbout();
        void handleAboutControl(bool&, bool&);
        void pauseGame();
        void handlePauseGameControl(bool&, bool&);

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




