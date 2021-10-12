/* Copyright (C) 2021 Chicken Escape authors */

#pragma once

#include <allegro5/allegro5.h>

class Game
{
public:
    void run();

private:
    void init();
    void cleanup();
    void actions();
    void draw();

    struct {
        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;
    } controls;

    enum { LEFT, RIGHT };

    struct {
        float x = 0;
        float y = 0;
        int lifepoints = 5;
        int orientation = RIGHT;
    } chicken;

    bool running = true;
    bool redraw = false;

    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;

    struct {
        ALLEGRO_BITMAP *chicken;
    } bitmaps;
};
