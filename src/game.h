/* Copyright (C) 2021 Chicken Escape authors */

#pragma once

#include <SDL.h>

class Game
{
public:
    void run();

private:
    void init();
    void cleanup();
    void handleEvent(SDL_Event &event);
    void actions();
    void draw();

    SDL_Texture* loadTextureFromBitmap(const char *path);

    SDL_Window *window;
    SDL_Renderer *renderer;

    struct {
        SDL_Texture *chicken;
        SDL_Texture *floor;
        SDL_Texture *wall;
    } textures;

    struct {
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;
    } controls;

    struct {
        int x = 0;
        int y = 0;
        int lifepoints = 5;
    } chicken;

    bool quit = false;
};
