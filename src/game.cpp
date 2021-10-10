/* Copyright (C) 2021 Chicken Escape authors */

#include "game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void Game::run()
{
    // Initialize SDL, load textures
    init();

    // Set the color for clearing the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    while (!quit)
    {
        // Handle all events that occurred
        SDL_Event event;
        while (SDL_PollEvent(&event)) handleEvent(event);

        // Clear the screen
        SDL_RenderClear(renderer);

        // Perform game actions
        actions();

        // Draw the screen
        draw();

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup before quit
    cleanup();
}

void Game::init()
{
    // Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a window with fixed size
    window = SDL_CreateWindow(
        "Chicken Escape",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // Create a window renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Load textures from bitmap files
    textures.chicken = loadTextureFromBitmap("chicken.bmp");
    textures.floor = loadTextureFromBitmap("floor.bmp");
    textures.wall = loadTextureFromBitmap("wall.bmp");
}

void Game::cleanup()
{
    SDL_DestroyTexture(textures.chicken);
    SDL_DestroyTexture(textures.floor);
    SDL_DestroyTexture(textures.wall);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::handleEvent(SDL_Event &event)
{
    switch (event.type)
    {
        case SDL_QUIT:
            quit = true;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT: controls.left = true; break;
                case SDLK_RIGHT: controls.right = true; break;
                case SDLK_UP: controls.up = true; break;
                case SDLK_DOWN: controls.down = true; break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT: controls.left = false;  break;
                case SDLK_RIGHT: controls.right = false; break;
                case SDLK_UP: controls.up = false; break;
                case SDLK_DOWN: controls.down = false; break;
            }
            break;
    }
}

void Game::actions()
{
    // Move the chicken
    if (controls.left)
    {
        chicken.orientation = LEFT;
        chicken.x -= 5;
    }
    if (controls.right)
    {
        chicken.orientation = RIGHT;
        chicken.x += 5;
    }
    if (controls.up) chicken.y -= 5;
    if (controls.down) chicken.y += 5;
}

void Game::draw()
{
    SDL_Rect rect;

    rect.w = 64;
    rect.h = 64;

    rect.x = chicken.x;
    rect.y = chicken.y;
    if (chicken.orientation == RIGHT)
        SDL_RenderCopy(renderer, textures.chicken, NULL, &rect);
    else if (chicken.orientation == LEFT)
        SDL_RenderCopyEx(renderer, textures.chicken, NULL, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);

    rect.x = 200;
    rect.y = 200;
    SDL_RenderCopy(renderer, textures.wall, NULL, &rect);

    rect.x = 200;
    rect.y = 136;
    SDL_RenderCopy(renderer, textures.wall, NULL, &rect);
}

SDL_Texture* Game::loadTextureFromBitmap(const char *path)
{
    SDL_Surface *surface = SDL_LoadBMP(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
