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
    }

    SDL_Quit();

    return 0;
}
