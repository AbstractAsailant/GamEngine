#include "GameOverScreen.hpp"
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <iostream>

GameOverScreen::GameOverScreen(int x, int y , int w, int h, std::string path, std::string message, SDL_Renderer* renderer, bool* isRunning){
    this->isRunning = isRunning;
    this->width = w;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    this->renderer = renderer;
    texture.LoadFromFile(path,renderer);
    this->message = message;
}

GameOverScreen::~GameOverScreen(){
    texture.Free();
}

void GameOverScreen::update(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        std::cout << "Event: " << e.type << std::endl;
        if(e.type == SDL_QUIT){
            *isRunning = false;
            std::cout << "Quit Event" << std::endl;
            isOpen = false;
        }
        if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_ESCAPE){
                isOpen = false;
                *isRunning = false;
                return;
            }
            if (e.key.keysym.sym == SDLK_SPACE){
                std::cout << "Space Pressed" << std::endl;
                isOpen = false;
                return;
            }
    }
}
}

void GameOverScreen::render(){
     // 1. Draw Background
    texture.Render(160/2, 160/2, renderer);

}