#include "GameLogic.hpp"
#include "PauseMenu.hpp"
#include "LTexture.hpp"
#include <iostream>
PauseMenu::PauseMenu(Window *window, SDL_Renderer* gameRenderer) {
    renderer = gameRenderer;
    this->window = window;
    isOpen = false;
    
    windowRect.x = Config::SCREEN_WIDTH / 2 - 30;
    windowRect.y = Config::SCREEN_HEIGHT / 2;
    windowRect.w = 160;
    windowRect.h = 160;
    // Load background
    texture.LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/pausemenu.png", renderer);
    
    // Initialize the button (Position it in the center of the screen)
    // Adjust these coordinates based on your actual button sprite/needs
    resumeButton = new Button(Config::SCREEN_WIDTH / 2 - 30, 
                                 Config::SCREEN_HEIGHT / 2, 
                                 100, 50, 
                                 "/home/marlboro/Desktop/GamEngine/assets/playbuttonnotpressed.png", 
                                 renderer);

    quitButton = new Button(220, 
                                 85, 
                                 100, 50, 
                                 "/home/marlboro/Desktop/GamEngine/assets/cookie.png",renderer);


     }

void PauseMenu::update(){
    SDL_Event E;
        while (SDL_PollEvent(&E)) {
            if (E.type == SDL_QUIT) {
                isOpen = false;
                exit(0); // Fully close the app
            }
            
            if (E.type == SDL_MOUSEBUTTONDOWN) {
                std::cout << "Mouse Button Down" << std::endl;
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point mousePoint = {x/3, y/3};
                    
                // Use SDL_PointInRect for mouse collisions
                std::cout << "Mouse Point: " << mousePoint.x << ", " << mousePoint.y << std::endl;
                std::cout << "Button Collider: " << resumeButton->getCollider()->x << ", " << resumeButton->getCollider()->y << std::endl;
                if (SDL_PointInRect(&mousePoint, resumeButton->getCollider())) {
                    std::cout << "Start Button Clicked!" << std::endl;
                    isOpen = false; // This exits the menu loop and starts the game
                }
            }
        }
}      

void PauseMenu::render() {
    // 1. Draw Background
    texture.Render(160/2, 160/2, renderer);

    // 2. Draw Button
   if (resumeButton != nullptr) {
        resumeButton->render();
    }

    if (quitButton != nullptr) {
        quitButton->render();
    }

}