/* Copyright (C) 2021 Chicken Escape authors */

#include <SDL.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
                             "Chicken Escape",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             800, 600, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Surface *chickenSurface = SDL_LoadBMP("chicken.bmp");
    SDL_Texture *chickenTexture = SDL_CreateTextureFromSurface(renderer, chickenSurface);
    SDL_FreeSurface(chickenSurface);

    SDL_Rect chickenRect {
        .x = 100,
        .y = 100,
        .w = chickenSurface->w,
        .h = chickenSurface->h
    };

    struct {
        bool left {false};
        bool right {false};
        bool up {false};
        bool down {false};
    } controls;

    bool quit {false};

    SDL_Event event;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:  controls.left = true;  break;
                        case SDLK_RIGHT: controls.right = true; break;
                        case SDLK_UP:    controls.up = true;    break;
                        case SDLK_DOWN:  controls.down = true;  break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:  controls.left = false;  break;
                        case SDLK_RIGHT: controls.right = false; break;
                        case SDLK_UP:    controls.up = false;    break;
                        case SDLK_DOWN:  controls.down = false;  break;
                    }
                    break;
            }
        }

        if (controls.left)  chickenRect.x -= 1;
        if (controls.right) chickenRect.x += 1;
        if (controls.up)    chickenRect.y -= 1;
        if (controls.down)  chickenRect.y += 1;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, chickenTexture, NULL, &chickenRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
