#include "Player.hpp"
#include "Game.hpp"
#include <SDL_events.h>
#include <SDL_rect.h>
#include <iostream>

Player::Player(int x, int y, int hp, int width, int height, bool isOnGround, PlayerState state, SDL_Renderer* renderer, std::string path) {
    setX(x);
    setY(y);
    setWidth(width);
    setHeight(height);
    setHP(hp);
    setState(state);
    this->renderer = renderer;
    texture.LoadFromFile(path, renderer);
    setIsOnGround(false);
}

void Player::handleInput(SDL_Event& E){
            if (getState()== PlayerState::Running && getIsOnGround()) {
                if (E.type == SDL_KEYDOWN) {
                    if (E.key.keysym.sym == SDLK_SPACE) {
                        jump();
                    }
                }
}
}

void Player::update(float deltaTime){
    if(!getIsOnGround()){
        //std::cout << "Player is falling" << std::endl;
        float temp;
        temp = getVelocityY(); // u0
        temp += getGravity()*deltaTime; // u(t) = u0 + gt
        setVelocityY(temp); // set u(t) as the new velocity
        setY(getY() + getVelocityY()*deltaTime); // set y(t) = y(t-1) + u(t)*dt
        // peak of jump is tpeak = -u0/g*dt
        if (getY() > Config::GROUND_HEIGHT-22) { // check if player is on the ground and make changes
            setY(Config::GROUND_HEIGHT-22);
            setVelocityY(0);
            setIsOnGround(true);
            setState(Player::PlayerState::Running);
           // std::cout << "Player is on the ground" << std::endl;
            return;
        }
        //else apply gravity
        
       // std::cout << "Player is falling" << std::endl;
    }
}

void Player::render(){
    texture.Render(getX(), getY(), renderer);
   // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //SDL_RenderDrawRect(renderer, &collider);
}

void Player::jump(){
    std::cout << "Jumping" << std::endl;
    setState(PlayerState::Jumping);
    setIsOnGround(false);
    setVelocityY(getJumpForce());
}