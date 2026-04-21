#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <iostream>

inline void CheckSDLError(const std::string& Action){
    const char* Error{SDL_GetError()};
    if(*Error != '\0'){
    std::cout << "Error, " << Action << " failed: " << Error << std::endl;
    }
    SDL_ClearError();
}