/* Copyright (C) 2021 Chicken Escape authors */

#include <stdio.h>
#include <allegro5/allegro_image.h>

#include "game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

const float FPS = 60;

void Game::init()
{
    al_init();

    al_init_image_addon();

    timer = al_create_timer(1.0 / FPS);

    display = al_create_display(800, 600);

    queue = al_create_event_queue();

    al_install_keyboard();

    al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    bitmaps.chicken = al_load_bitmap("chicken.bmp");

    al_set_display_icon(display, bitmaps.chicken);
}

void Game::run()
{
    // Initialize the game
    init();

    al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

    al_start_timer(timer);

    // Main loop
    while (running)
    {
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);

        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                actions();
                redraw = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT: controls.left = true; break;
                    case ALLEGRO_KEY_RIGHT: controls.right = true; break;
                    case ALLEGRO_KEY_UP: controls.up = true; break;
                    case ALLEGRO_KEY_DOWN: controls.down = true; break;
                }
                break;

            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT: controls.left = false; break;
                    case ALLEGRO_KEY_RIGHT: controls.right = false; break;
                    case ALLEGRO_KEY_UP: controls.up = false; break;
                    case ALLEGRO_KEY_DOWN: controls.down = false; break;
                }
                break;
        }

		if (redraw && al_is_event_queue_empty(queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
			draw();
			al_flip_display();
			redraw = false;
		}
    }

    // Cleanup before quit
    cleanup();
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
    if (chicken.orientation == RIGHT)
        al_draw_bitmap(bitmaps.chicken, chicken.x, chicken.y, 0);
    else if (chicken.orientation == LEFT)
        al_draw_bitmap(bitmaps.chicken, chicken.x, chicken.y, ALLEGRO_FLIP_HORIZONTAL);
}

void Game::cleanup()
{
}
