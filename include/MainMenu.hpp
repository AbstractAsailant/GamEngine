#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <string>
#include "GameLogic.hpp"
#include "LTexture.hpp"
#include "Button.hpp"
#include "Window.hpp"
#include <SDL2/SDL.h>
#include <vector>
class MainMenu {
public:
    // Pass the renderer from the Game class so we don't crash
    MainMenu(Window *window, SDL_Renderer* gameRenderer);

    ~MainMenu();

    void run();

    void update();

    void render();

    bool isMenuOpen();

private:
    LTexture texture;
    SDL_Renderer* renderer = nullptr;
    Button* startButton = nullptr;
    Window* window;
    bool isOpen;
};

#endif