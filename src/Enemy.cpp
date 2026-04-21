#include "Enemy.hpp"
#include "GameLogic.hpp"

Enemy::Enemy(int x, int y, int width, int height, std::string path, SDL_Renderer* rendererr) {
    setX(x);
    setY(y);
    setWidth(width);
    setHeight(height);
    renderer = rendererr;
    texture.LoadFromFile(path, renderer);
}

void Enemy::update(){
    //std::cout << "Updating Enemy" << std::endl;
    if(getY() > Config::GROUND_HEIGHT){
        setY(Config::GROUND_HEIGHT);
    }
    if(offsetX+32 < 0){
        offsetX = 320;
    }
    offsetX -= Config::GROUND_OFFSET;
    if(offsetX < -Config::SCREEN_WIDTH){
        offsetX = 0;
    }
    setX((int)offsetX);
}

void Enemy::render(){
    texture.Render((int)offsetX, getY(), renderer);
}