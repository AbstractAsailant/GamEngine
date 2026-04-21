#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include "GameLogic.hpp"
#include "LTexture.hpp"

class Player {
public:
    int getX(){
        return collider.x;
    }

    int getY(){
        return collider.y;
    }

    void setX(int x){
        collider.x = x;
    }

    void setY(int y){
        collider.y = y;
    }

    void setWidth(int width){
        collider.w = width;
    }

    void setHeight(int height){
        collider.h = height;
    }

    int getHeight(){
        return collider.h;
    }

    int getWidth(){
        return collider.w;
    }

    void setIsOnGround(bool isOnGround){
        this->isOnGround = isOnGround;
    }

    bool getIsOnGround(){
        return isOnGround;
    }

    void animationHandler();

    void jump();

    void render();

    void update(float deltaTime);

    int getHP(){
        return hp;
    }

    void setHP(int hp){
        this->hp = hp;
    }

    void handleInput();

    enum class PlayerState { Idle, Jumping, Falling, Dead, Hit, Landing, Running };

    PlayerState getState(){
        return state;
    }

    void setState(PlayerState state){
        this->state = state;
    }


    Player(int x, int y, int hp, int width, int height, bool isOnGround, PlayerState state, SDL_Renderer* renderer, std::string path);
    
    const float getVelocityX(){
        return velocityX;
    }

    const float getVelocityY(){
        return velocityY;
    }

    void setVelocityY(float velocityY){
        this->velocityY = velocityY;
    }

    void setVelocityX(float velocityX){
        this->velocityX = velocityX;
    }

    const float getGravity(){
        return gravity;
    }

    const float getJumpForce(){
        return jumpForce;
    }

    void setCollider(SDL_Rect ccollider){
        collider = ccollider;
    }

    void setTexture(SDL_Texture* texture){
        sdltexture = texture;
    }

    SDL_Texture* getTexture(){
        return sdltexture;
    }

    const SDL_Rect* getCollider() const { return &collider; }

    void handleInput(SDL_Event& E);

    void setInvis(bool isInvis){
        this->isInvis = isInvis;
    }

    bool getInvis(){
        return isInvis;
    }
    void setIframes(int iFrames){
        this->iFrames = iFrames;
    }

    int getIframes(){
        return iFrames;
    }
private:
    int hp;
    SDL_Rect collider;
    float velocityY;
    float velocityX;
    bool isOnGround;
    const float gravity = 3000.0f;
    const float jumpForce = -700.0f;
    PlayerState state;
    SDL_Renderer* renderer;
    LTexture texture;
    SDL_Texture* sdltexture;
    bool isInvis = false;
    int iFrames = 30;
};

#endif // PLAYER_HPP