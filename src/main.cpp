#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#include <iostream>

#include "Game.h"
using namespace std;


#if defined(_WIN32) || defined(_WIN64)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif
#ifdef __unix__
int main (int argc, char *argv[]){
#endif
    Game *game = new Game();
    game->newGame();
    delete game;
    return 0;
}