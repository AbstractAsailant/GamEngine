#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include "GameLogic.hpp"
#include "LTexture.hpp"
#include "Button.hpp"
#include "Window.hpp"
#include <SDL2/SDL.h>
#include <SDL_rect.h>
#include <vector>

class PauseMenu {
public:
    PauseMenu(Window *window, SDL_Renderer* gameRenderer);

    ~PauseMenu(){
        delete resumeButton;
        delete quitButton;
        texture.Free();
    };

    void run();

    void update();

    void render();

    bool isMenuOpen(){
        return isOpen;
    }

    void setIsOpen(bool isOpen){
        this->isOpen = isOpen;
    }

private:
    LTexture texture;
    SDL_Rect windowRect;
    SDL_Renderer* renderer = nullptr;
    Button* resumeButton = nullptr;
    Button* quitButton = nullptr;
    Window* window;
    bool isOpen;
};

#endif