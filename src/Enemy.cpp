#include "Enemy.hpp"
#include "GameLogic.hpp"
#include "Player.hpp"
#include <random>
#include <iostream>
Enemy::Enemy(int x, int y, int width, int height, std::string path, SDL_Renderer* rendererr) {
    setX(x);
    setY(y);
    setWidth(width);
    setHeight(height);
    setPassed(false);
    offsetX = x;
    renderer = rendererr;
    texture.LoadFromFile(path, renderer);
}

Enemy::~Enemy(){
    delete renderer;
}

void Enemy::update(float deltaTime){
    //std::cout << "Updating Enemy" << std::endl;
    if(offsetX+32 < 0){
        // Define range
         // define minimum distance to leave space for player
         int min = Config::minDistance;
         std::cout<<"Min: "<<min<<std::endl;
         int max = 10;
         // Initialize a random number generator
         std::random_device rd;
         std::mt19937 gen(rd());
         std::uniform_int_distribution<> distrib(min, max);
        // Generate random number in the range [min, max]
            int randomValue = distrib(gen);
             hasBeenPassed = false;
           offsetX = 320 + 32*randomValue;
    }
    offsetX -= Config::GROUND_OFFSET;
    if(offsetX < -Config::SCREEN_WIDTH){
        offsetX = 0;
    }
    setX((int)offsetX);
}

void Enemy::render(){
    texture.Render((int)offsetX, getY(), renderer);
   SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &clip);
}

void Enemy::changeSprite(std::string path){
    texture.LoadFromFile(path, renderer);
}