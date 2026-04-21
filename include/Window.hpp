#pragma once
#include "GameLogic.hpp"
class Window {
public:
    Window() {
       SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
        SDLWindow = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Config::SCREEN_WIDTH*3, Config::SCREEN_HEIGHT*3, SDL_WINDOW_SHOWN);
        // Create the Renderer (GPU tool)
        SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_RenderSetLogicalSize(SDLRenderer, Config::SCREEN_HEIGHT, Config::SCREEN_HEIGHT);
        IMG_Init(IMG_INIT_PNG);
    }

    void Clear() {
        SDL_SetRenderDrawColor(SDLRenderer, 50, 50, 50, 255); // Dark grey
        SDL_RenderClear(SDLRenderer);
    }

    void Present() {
        SDL_RenderPresent(SDLRenderer);
    }

    SDL_Renderer* GetRenderer() { return SDLRenderer; }

    ~Window() {
        SDL_DestroyRenderer(SDLRenderer);
        SDL_DestroyWindow(SDLWindow);
        IMG_Quit();
    }

private:
    SDL_Window* SDLWindow = nullptr;
    SDL_Renderer* SDLRenderer = nullptr;
};