#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace Config {
    inline constexpr int TARGET_FPS = 60;
    inline constexpr float physicsDeltaTime = 1.0 / (float)TARGET_FPS;
    inline constexpr int FRAME_DELAY = 1000 / TARGET_FPS;
    inline constexpr int PLAYER_WIDTH = 32;
    inline constexpr int PLAYER_HEIGHT = 32;
    inline constexpr int TILE_HEIGHT = 32;
    inline constexpr int TILE_WIDTH = 32;
    inline constexpr int MAP_WIDTH = 10;
    inline constexpr int MAP_HEIGHT = 10;
    inline constexpr int SCREEN_WIDTH = TILE_WIDTH * MAP_WIDTH;
    inline constexpr int SCREEN_HEIGHT = TILE_HEIGHT * MAP_HEIGHT;
    inline constexpr int GROUND_HEIGHT = SCREEN_HEIGHT - 3*TILE_HEIGHT;
    inline constexpr float BACKGROUND_OFFSET = 0.6f;
    inline constexpr float GROUND_OFFSET = 3.0f;
    inline constexpr float CLOUD_OFFSET = 0.4f;
    inline constexpr float GRAVITY = 2.6f;
    inline constexpr float JUMP_FORCE = -4.0f;
    inline float uWorld = GROUND_OFFSET/physicsDeltaTime;
    inline constexpr float jumpPeak = (-JUMP_FORCE/GRAVITY)*physicsDeltaTime;
    inline constexpr float jumpTime = 2.0f*jumpPeak;
    inline float minDistance = uWorld*jumpTime;
}
#endif // GAMELOGIC_HPP