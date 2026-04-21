#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "LTexture.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_rect.h>
#include <string>

class Button {
public:
    Button(int x, int y, int width, int height, std::string path, SDL_Renderer* renderer){
        texture.LoadFromFile(path, renderer);
        clip.x = x;
        clip.y = y;
        clip.w = width;
        clip.h = height;
        this->renderer = renderer;
        isPressed = false;
    };
    ~Button(){
        texture.Free();
    }

    void update();
    void render(){
        texture.Render(clip.x, clip.y, renderer);
    }
    void handleClick();
    SDL_Rect* getCollider(){
        return &clip;
    }
    private:
    LTexture texture;
    SDL_Rect clip; 
    SDL_Renderer* renderer;
    bool isPressed = false;
    
};

#endif // BUTTON_HPP