#include "GameLogic.hpp"
#include "MainMenu.hpp"
#include "LTexture.hpp"
#include "Button.hpp"
#include "Window.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <iostream>

    // Pass the renderer from the Game class so we don't crash

    MainMenu::MainMenu(Window *window, SDL_Renderer* gameRenderer) {
        renderer = gameRenderer;
        this->window = window;
        isOpen = true;
        
        // Load background
        texture.LoadFromFile("/home/marlboro/Desktop/GamEngine/assets/mainmenu.png", renderer);
        
        // Initialize the button (Position it in the center of the screen)
        // Adjust these coordinates based on your actual button sprite/needs
        startButton = new Button(Config::SCREEN_WIDTH / 2 - 30, 
                                 Config::SCREEN_HEIGHT / 2, 
                                 100, 50, 
                                 "/home/marlboro/Desktop/GamEngine/assets/playbuttonnotpressed.png", 
                                 renderer);
    }

    MainMenu::~MainMenu() {
    delete startButton;
    texture.Free();
}

   void MainMenu::run() {
        while (isOpen) {
            update();
            render();
        }
    }

    void MainMenu::update() {
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
                std::cout << "Button Collider: " << startButton->getCollider()->x << ", " << startButton->getCollider()->y << std::endl;
                if (SDL_PointInRect(&mousePoint, startButton->getCollider())) {
                    std::cout << "Start Button Clicked!" << std::endl;
                    isOpen = false; // This exits the menu loop and starts the game
                }
            }
        }
    }
    void MainMenu::render() {
        window->Clear();
        // 1. Draw Background
        texture.Render(0, 0, renderer);

        // 2. Draw Button
       if (startButton != nullptr) {
            startButton->render();
        }

        window->Present();
    }

    bool MainMenu::isMenuOpen() {
        return isOpen;
    }