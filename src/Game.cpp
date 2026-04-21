#include "Game.hpp"
#include "GameLogic.hpp"
#include "MainMenu.hpp"
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_timer.h>
#include <iostream>
#include <SDL_ttf.h>
Game::Game(Window *window) {
    gameWindow = window;
    isRunning = true;
    if (TTF_Init() == -1) {
        std::cout << "Failed to init TTF" << std::endl;
    }
    font = TTF_OpenFont("/home/marlboro/Desktop/GamEngine/assets/font.TTF", 12);
        if (font == nullptr) {
            std::cout << "Failed to load font" << std::endl;
        }
        scoreTexture = new LTexture();
    // 1. Create Texture Utility
    groundTexture = new LTexture();
    backgroundTexture = new LTexture();
    cloudTexture = new LTexture();
    // 2. Load the actual image file
    groundTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/groundtilegroup.png", gameWindow->GetRenderer());
    backgroundTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/background.png", gameWindow->GetRenderer());
    cloudTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/clouds.png", gameWindow->GetRenderer());

    // 3. Create Player (Pass the renderer so it knows how to draw)
    player = new Player(0, 0, 100, 32, 32, true, 
                        Player::PlayerState::Running, 
                        gameWindow->GetRenderer(), 
                        "/home/marlboro/Desktop/GamEngine/assets/purin");


    enemy = new Enemy(320, Config::GROUND_HEIGHT-32,32,32,"/home/marlboro/Desktop/GamEngine/assets/pudding.png", gameWindow->GetRenderer());
    // 4. Create Ground (Pass the renderer so it knows how to draw) 
}

void Game::run() {
    int frames = 0;
       // std::cout << "Running" << std::endl;
       //main menu
        uint32_t frameStart;
        int frametime;
        uint32_t lastFrameStart = 0;
        while (isRunning) {
                frameStart = SDL_GetTicks();
                deltaTime = (frameStart - lastFrameStart)/1000.0f;
                std::cout << "Delta Time: " << deltaTime << std::endl;
                lastFrameStart = frameStart;
                update(deltaTime);
                render();
                frametime = SDL_GetTicks() - frameStart;
                if (frametime < FRAME_DELAY) {
                    SDL_Delay(FRAME_DELAY - frametime);
                }
                // SDL_Delay(Config::TARGET_FPS);
            }
        }

void Game::update(float deltaTime) {
    if (SDL_HasIntersection(player->getCollider(), enemy->getCollider())) {
        isRunning = false;
        std::cout << "Collision" << std::endl;
        return;
    }
    enemy->update();
    player->update(deltaTime);
    SDL_Event E;
    while (SDL_PollEvent(&E)) {
        if (E.type == SDL_QUIT) isRunning = false;
        player->handleInput(E);
    }
   // std::cout << "Updating" << std::endl;
    //scroll physuics
    backgroundOffset -= Config::BACKGROUND_OFFSET;
    groundOffset -= Config::GROUND_OFFSET;
    if ((int)groundOffset % 32 == 0){
        updateScore();
    }
    cloudOffset -= Config::CLOUD_OFFSET;
    if (backgroundOffset < -Config::SCREEN_WIDTH) {
        backgroundOffset = 0;
    }

    if (groundOffset < -Config::SCREEN_WIDTH) {
        groundOffset = 0;
    }

    if (cloudOffset < -Config::SCREEN_WIDTH) {
        cloudOffset = 0;
    }
   // std::cout << "Rendering" << std::endl;
}

void Game::render() {
    gameWindow->Clear();
    backgroundTexture->Render((int)backgroundOffset, 0, gameWindow->GetRenderer());
    backgroundTexture->Render((int)backgroundOffset + 320, 0, gameWindow->GetRenderer());
    groundTexture->Render((int)groundOffset + 320, Config::GROUND_HEIGHT, gameWindow->GetRenderer());
    groundTexture->Render((int)groundOffset, Config::GROUND_HEIGHT, gameWindow->GetRenderer());
    cloudTexture->Render((int)cloudOffset, 0, gameWindow->GetRenderer());
    cloudTexture->Render((int)cloudOffset + 320, 0, gameWindow->GetRenderer());

    // Use the LTexture to draw the player at its current X and Y
    player->render();
    enemy->render();

    if (scoreTexture != nullptr){
        scoreTexture->Render(220, 0, gameWindow->GetRenderer());
    }
    gameWindow->Present();
   // std::cout << "Rendered" << std::endl;
}

Game::~Game() {
    delete player;
    delete playerTexture;
    delete groundTexture;
    delete backgroundTexture;
    delete cloudTexture;
    delete gameWindow;
}

void Game::updateScore(){
    score++;
    SDL_Color textColor = { 255, 255, 255, 255 };
    std::string scoreText = "Score: " + std::to_string(score);
    if (scoreTexture->LoadFromRenderedText(scoreText, font, textColor, gameWindow->GetRenderer())) {
        std::cout << "Score: " << score << std::endl;
    }
}