/* Copyright (C) 2021 Chicken Escape authors */

#include <stdio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const float FPS = 60;

void Game::init()
{
    al_init();

    al_init_image_addon();
    
    timer = al_create_timer(1.0 / FPS);

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

    queue = al_create_event_queue();

    al_install_keyboard();

    al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    bitmaps.chicken = al_load_bitmap("chicken.bmp");
    bitmaps.floor = al_load_bitmap("floor.bmp");
    bitmaps.wall = al_load_bitmap("wall.bmp");

    al_set_display_icon(display, bitmaps.chicken);

    create_map(52, 31, 0.1);
    build_maze();
    draw_map();

    init_audio();
}

void Game::run()
{
    // Initialize the game
    init();

    al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

    al_start_timer(timer);
    
    play_music();

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
                sfx_walk(true);
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_LEFT: controls.left = true; break;
                    case ALLEGRO_KEY_RIGHT: controls.right = true; break;
                    case ALLEGRO_KEY_UP: controls.up = true; break;
                    case ALLEGRO_KEY_DOWN: controls.down = true; break;
                    case ALLEGRO_KEY_M: control_audio(); break;
                    case ALLEGRO_KEY_PGDN: control_music_volume(1); break;
                    case ALLEGRO_KEY_PGUP: control_music_volume(2); break;
                }
                break;

            case ALLEGRO_EVENT_KEY_UP:
                sfx_walk(false);
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
    int cur_x, cur_y, new_x, new_y;
    cur_x = static_cast<int>(chicken.maze_x / 64);
    cur_y = static_cast<int>(chicken.maze_y / 64);
    if (controls.left)
    {
        new_x = static_cast<int>((chicken.maze_x - chicken.speed) / 64);
        new_y = static_cast<int>(chicken.maze_y / 64);
        if (cur_x == new_x)
        {
            chicken.maze_x -= chicken.speed;
        }
        else
        {
            
            if (chicken.maze_y % 64 == 0)
            {
                if(!get_wall(new_x, new_y))
                {
                    chicken.maze_x -= chicken.speed;
                }   
            }
            else
            {
                if (!get_wall(new_x, new_y) && !get_wall(new_x, new_y + 1))
                {
                    chicken.maze_x -= chicken.speed;
                }
            }
        }
        chicken.lookleft = true;
    }

    if (controls.right)
    {
        new_x = static_cast<int>((chicken.maze_x + chicken.speed) / 64);
        new_y = static_cast<int>(chicken.maze_y / 64);
        if (cur_x == new_x)
        {
            chicken.maze_x += chicken.speed;
        }
        else
        {
            
            if (chicken.maze_y % 64 == 0)
            {
                if(!get_wall(new_x + 1, new_y))
                {
                    chicken.maze_x += chicken.speed;
                }   
            }
            else
            {
                if (!get_wall(new_x + 1, new_y) && !get_wall(new_x + 1, new_y + 1))
                {
                    chicken.maze_x += chicken.speed;
                }
            }
        }
        chicken.lookleft = false;
    }

    if (controls.up)
    {
        new_x = static_cast<int>(chicken.maze_x / 64);
        new_y = static_cast<int>((chicken.maze_y - chicken.speed) / 64);
        if (cur_y == new_y)
        {
            chicken.maze_y -= chicken.speed;
        }
        else
        {
            
            if ((chicken.maze_x) % 64 == 0)
            {
                if(!get_wall(new_x, new_y))
                {
                    chicken.maze_y -= chicken.speed;
                }   
            }
            else
            {
                if (!get_wall(new_x, new_y) && !get_wall(new_x + 1, new_y))
                {
                    chicken.maze_y -= chicken.speed;
                }
            }
        }
    }

    if (controls.down)
    {
        new_x = static_cast<int>(chicken.maze_x / 64);
        new_y = static_cast<int>((chicken.maze_y + chicken.speed) / 64);
        if (cur_y == new_y)
        {
            chicken.maze_y += chicken.speed;
        }
        else
        {
            
            if (chicken.maze_x % 64 == 0)
            {
                if(!get_wall(new_x, new_y + 1))
                {
                    chicken.maze_y += chicken.speed;
                }   
            }
            else
            {
                if (!get_wall(new_x, new_y + 1) && !get_wall(new_x + 1, new_y + 1))
                {
                    chicken.maze_y += chicken.speed;
                }
            }
        }
    }

    if (chicken.maze_x <= SCREEN_WIDTH / 2 - 32)
        map.x = 0;
    else if ((chicken.maze_x > SCREEN_WIDTH / 2 - 32) && (chicken.maze_x <= map.pixel_width - (SCREEN_WIDTH / 2 + 32)))
        map.x = -(chicken.maze_x - (SCREEN_WIDTH / 2 - 32));
    else
        map.x = -(map.pixel_width - SCREEN_WIDTH);

    if (chicken.maze_y <= SCREEN_HEIGHT / 2 - 32)
        map.y = 0;
    else if ((chicken.maze_y > SCREEN_HEIGHT / 2 - 32) && (chicken.maze_y <= map.pixel_height - (SCREEN_HEIGHT / 2 + 32)))
        map.y = -(chicken.maze_y - (SCREEN_HEIGHT / 2 - 32));
    else
        map.y = -(map.pixel_height - SCREEN_HEIGHT);

    chicken.x = chicken.maze_x + map.x;
    chicken.y = chicken.maze_y + map.y;
    
}

void Game::draw()
{
    al_draw_bitmap(map.bitmap, map.x, map.y, 0);

    int flags = chicken.lookleft ? ALLEGRO_FLIP_HORIZONTAL : 0;
    al_draw_bitmap(bitmaps.chicken, chicken.x, chicken.y, flags);
}

void Game::cleanup()
{
}

