#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "GameLogic.hpp"
#include "LTexture.hpp"
#include <SDL_render.h>
#include <string>

class Enemy {
public:
    Enemy(int x, int y, int width, int height, std::string path, SDL_Renderer* renderer);
    ~Enemy();

    void update();
    void render();

    void setX(int x){
        clip.x = x;
    }
    void setY(int y){
        clip.y = y;
    }

    int getX(){
        return clip.x;
    }

    int getY(){
        return clip.y;
    }

    int getWidth(){
        return clip.w;
    }

    int getHeight(){
        return clip.h;
    }

    void setWidth(int width){
        clip.w = width;
    }

    void setHeight(int height){
        clip.h = height;
    }

    const SDL_Rect* getCollider() const { return &clip; }

private:
    LTexture texture;
    SDL_Rect clip;
    SDL_Renderer* renderer;
    float offset = Config::GROUND_OFFSET;
    float offsetX = 320;
};





#endif // ENEMY_HPP