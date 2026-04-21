#include <SDL2/SDL.h>
#include "Game.hpp"
#include "MainMenu.hpp"
#include "ctime"
int main(int argc, char** argv) {
    std::srand(std::time(nullptr));
    SDL_Init(SDL_INIT_VIDEO);

    Window *gameWindow = new Window();
    MainMenu mainMenu = MainMenu(gameWindow, gameWindow->GetRenderer());
    //create main menu
    mainMenu.run();
    Game myGame = Game(gameWindow);
    myGame.run(); // Everything happens inside here

    SDL_Quit();
    return 0;
}