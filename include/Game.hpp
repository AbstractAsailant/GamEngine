#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"
#include "Player.hpp"
#include "LTexture.hpp"
#include "Enemy.hpp"
#include "PauseMenu.hpp"
#include "GameOverScreen.hpp"
class Game {
public:
    Game(Window *window);
    ~Game();

    void run();    // This is the heart of the engine
    void update(float deltaTime);
    void render();
    void updateScore();
    void restartGame();
    void setIsRunning(bool isRunning){
        this->isRunning = isRunning;
    }
    bool getIsRunning(){
        return this->isRunning;
    }

private:
    float backgroundOffset = 0;
    float groundOffset = 0;
    float cloudOffset = 0;
    bool isRunning;
    Window* gameWindow;
    Player* player;
    LTexture* playerTexture;
    LTexture* groundTexture;
    LTexture* backgroundTexture;
    LTexture* cloudTexture;
    Enemy* enemy;
    Enemy* secondEnemy;
    int score = 0;
    LTexture* scoreTexture;
    TTF_Font* font = nullptr;
    LTexture* hpTexture;
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;
    float deltaTime = 0;
    bool paused = false;
    PauseMenu* pMenu;
    GameOverScreen* overScreen;
};

#endif