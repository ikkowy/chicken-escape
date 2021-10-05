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

    SDL_Surface *windowSurface = SDL_GetWindowSurface(window);

    SDL_Surface *chickenSurface = SDL_LoadBMP("chicken.bmp");

    bool quit {false};

    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        SDL_BlitSurface(chickenSurface, NULL, windowSurface, NULL);

        SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(windowSurface);

    SDL_FreeSurface(chickenSurface);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
