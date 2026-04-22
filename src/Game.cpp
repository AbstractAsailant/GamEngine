#include "Game.hpp"
#include "GameLogic.hpp"
#include "MainMenu.hpp"
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_timer.h>
#include <iostream>
#include <SDL_ttf.h>
#include <GameOverScreen.hpp>
Game::Game(Window *window) {
    gameWindow = window;
    isRunning = true;
    std::cout << "Game Constructor" << std::endl;
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
    hpTexture = new LTexture();
    // 2. Load the actual image file
    groundTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/groundtilegroup.png", gameWindow->GetRenderer());
    backgroundTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/background.png", gameWindow->GetRenderer());
    cloudTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/clouds.png", gameWindow->GetRenderer());
    hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp3.png", gameWindow->GetRenderer());

    // 3. Create Player (Pass the renderer so it knows how to draw)
    player = new Player(10, 100, 3, 20, 18, true, 
                        Player::PlayerState::Running, 
                        gameWindow->GetRenderer(), 
                        "/home/marlboro/Desktop/GamEngine/assets/purin.png");


    enemy = new Enemy(320, Config::GROUND_HEIGHT-29,32,29,"/home/marlboro/Desktop/GamEngine/assets/pudding.png", gameWindow->GetRenderer());         
    secondEnemy = new Enemy(480, Config::GROUND_HEIGHT-29,32,29,"/home/marlboro/Desktop/GamEngine/assets/pudding.png", gameWindow->GetRenderer());
    pMenu = new PauseMenu(gameWindow, gameWindow->GetRenderer());
    overScreen = new GameOverScreen(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "/home/marlboro/Desktop/GamEngine/assets/playbuttonnotpressed.png", "Game Over", gameWindow->GetRenderer(), &isRunning);
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
                //std::cout << "Delta Time: " << deltaTime << std::endl;
                lastFrameStart = frameStart;
                if (secondEnemy->getNextStage() == false && score >= 200 && secondEnemy->getX() > 320){
                    secondEnemy->setNextStage(true);
                    std::cout << "Setting next stage" << std::endl;
                    secondEnemy->changeSprite("/home/marlboro/Desktop/GamEngine/assets/biscuit.png");
                    secondEnemy->setWidth(24);
                    secondEnemy->setHeight(56);
                    secondEnemy->setY(Config::GROUND_HEIGHT-56);
                    
                }
                if (isRunning == false){
                std::cout << "is running is " << isRunning << std::endl;
                }
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
    if(overScreen->isGameOverScreenOpen() == true){
        overScreen->update();
        if(overScreen->isGameOverScreenOpen() == false && isRunning == true){
            restartGame();
        }
        return;
    }
    if (pMenu->isMenuOpen() == true){
        pMenu->update();
        return;
    }
    if (player->getInvis() == true && player->getIframes() > 0){
        player->setIframes(player->getIframes()-1);
    }
    if (player->getInvis() == true && player->getIframes() <= 0){
        player->setInvis(false);
        player->setIframes(30);
    }
    if (SDL_HasIntersection(player->getCollider(), enemy->getCollider()) && player->getInvis() == false) {
        player->setHP(player->getHP() - 1);
        switch (player->getHP()){
            case 3:
                hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp3.png", gameWindow->GetRenderer());
                break;
            case 2:
                hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp2.png", gameWindow->GetRenderer());
                break;
            case 1:
                hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp1.png", gameWindow->GetRenderer());
                break;
            default:
            hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp0.png", gameWindow->GetRenderer());
                overScreen->setIsOpen(true);
                return;
                break;
        }
        player->setInvis(true);
        std::cout << "Collision" << std::endl;
        return;
    }
    if (SDL_HasIntersection(player->getCollider(), secondEnemy->getCollider()) && player->getInvis() == false) {
        player->setHP(player->getHP() - 1);
        switch (player->getHP()){
            case 3:
                hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp3.png", gameWindow->GetRenderer());
                break;
            case 2:
                hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp2.png", gameWindow->GetRenderer());
                break;
            case 1:
                hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp1.png", gameWindow->GetRenderer());
                break;
            default:
                hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp0.png", gameWindow->GetRenderer());
                overScreen->setIsOpen(true);
                return;
                break;
        }

        player->setInvis(true);
        std::cout << "Collision" << std::endl;
        return;
    }
    if(enemy->getX() < player->getX() && enemy->isPassed() == false){
        enemy->setPassed(true);
        score += 12;
    }
    if(secondEnemy->getX() < player->getX() && secondEnemy->isPassed() == false){
        secondEnemy->setPassed(true);
        if(secondEnemy->getNextStage() == false){
        score += 12;
        }
        else{
            score += 24;
        }
    }
    enemy->update(deltaTime);
    secondEnemy->update(deltaTime);
    if( std::abs(enemy->getOffsetX() - secondEnemy->getOffsetX()) < 64 || std::abs(secondEnemy->getOffsetX() - enemy->getOffsetX()) < 64){
        std::cout<<"fixing"<<std::endl;
        if (enemy->getOffsetX() > secondEnemy->getOffsetX()){
            enemy->setOffsetX(enemy->getOffsetX() + 128);
        }
        else{
            secondEnemy->setOffsetX(secondEnemy->getOffsetX() + 128);
        }
    }
    player->update(deltaTime);
    SDL_Event E;
    while (SDL_PollEvent(&E)) {
        if (E.type == SDL_QUIT) isRunning = false;
        if (E.type == SDL_KEYDOWN) {
            if (E.key.keysym.sym == SDLK_p) {
                pMenu->setIsOpen(!pMenu->isMenuOpen());
                return;
            }
        }
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
    secondEnemy->render();

    if (scoreTexture != nullptr){
        scoreTexture->Render(220, 0, gameWindow->GetRenderer());
    }
    hpTexture->Render(0, 0, gameWindow->GetRenderer());

    if (pMenu != nullptr && pMenu->isMenuOpen() && !overScreen->isGameOverScreenOpen()){
        SDL_SetRenderDrawBlendMode(gameWindow->GetRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(gameWindow->GetRenderer(), 0, 0, 0, 150); // Semi-transparent black
        SDL_Rect fullScreen = {0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT};
        SDL_RenderFillRect(gameWindow->GetRenderer(), &fullScreen);
        pMenu->render();
    }
    if (overScreen != nullptr && overScreen->isGameOverScreenOpen()){
       // std::cout << "Rendering Game Over" << std::endl;
        SDL_SetRenderDrawBlendMode(gameWindow->GetRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(gameWindow->GetRenderer(), 0, 0, 0, 150); // Semi-transparent black
        SDL_Rect fullScreen = {0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT};
        SDL_RenderFillRect(gameWindow->GetRenderer(), &fullScreen);
        overScreen->render();
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
    delete enemy;
    delete secondEnemy;
    delete scoreTexture;
    delete font;
    TTF_Quit();
}

void Game::updateScore(){
    score++;
    SDL_Color textColor = { 255, 255, 255, 255 };
    std::string scoreText = "Score: " + std::to_string(score);
    if (scoreTexture->LoadFromRenderedText(scoreText, font, textColor, gameWindow->GetRenderer())) {
        std::cout << "Score: " << score << std::endl;
    }
}

void Game::restartGame(){
    std::cout << "Restarting Game" << std::endl;
    player->restart();
    enemy->restart();
    secondEnemy->restart();
    hpTexture->LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/hp3.png", gameWindow->GetRenderer());
    score = 0;
    float backgroundOffset = 0;
    float groundOffset = 0;
    float cloudOffset = 0;
}