#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include "LTexture.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_render.h>
#include <iostream>
#include <string>
#include <vector>
#include <LTexture.hpp>
class GameOverScreen{
    public:
        GameOverScreen(int x, int y , int w, int h, std::string path, std::string message, SDL_Renderer* renderer, bool* isRunning);
        ~GameOverScreen();
        void update();
        void render();
        bool isGameOverScreenOpen(){
            return isOpen;
        }
        void setIsOpen(bool isOpen){
            this->isOpen = isOpen;
        }
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TTF_Font* font;
        SDL_Rect rect;
        LTexture texture;
        std::string message;
        int width;
        bool isOpen = false;
        bool *isRunning;

};



#endif // GAMEOVERSCREEN_HPP