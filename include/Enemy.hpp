#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "GameLogic.hpp"
#include "LTexture.hpp"
#include <SDL_render.h>
#include <cstdlib>
#include <string>

class Enemy {
public:
    Enemy(int x, int y, int width, int height, std::string path, SDL_Renderer* renderer);
    ~Enemy();

    void update(float deltaTime);
    void render();

 void changeSprite(std::string path);

    int getOffsetX(){
        return offsetX;
    };

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

    bool isPassed(){
        return hasBeenPassed;
    }

    void setPassed(bool passed){
        hasBeenPassed = passed;
    }

    void setOffsetX(float offsetX){
        this->offsetX = offsetX;
        setX((int)offsetX);
    }

    bool getNextStage(){
        return nextStage;
    }

    void setNextStage(bool nextStage){
        this->nextStage = nextStage;
    }
private:
    LTexture texture;
    SDL_Rect clip;
    SDL_Renderer* renderer;
    float offset = Config::GROUND_OFFSET;
    float offsetX = 320;
    bool hasBeenPassed = false;
    bool nextStage = false;
};





#endif // ENEMY_HPP