/* Copyright (C) 2021 Chicken Escape authors */

#include "game.h"

void Game::create_map(int bw, int bh)
{
    map.block_width = bw;
    map.block_height = bh;
    map.pixel_width = map.block_width * BLOCK_SIZE;
    map.pixel_height = map.block_height * BLOCK_SIZE;
    map.bitmap = al_create_bitmap(map.pixel_width, map.pixel_height);
    map.walls = std::vector<bool>(map.block_width * map.block_height, 0);
}

void Game::build_maze()
{
    set_wall(0,0);
    set_wall(1,0);
    set_wall(1,1);
}

void Game::draw_map()
{
    al_set_target_bitmap(map.bitmap);

    for (int i=0; i < map.block_width; i++)
    {
        for (int j=0; j < map.block_height; j++)
        {
            ALLEGRO_BITMAP *bitmap = get_wall(i, j) ? bitmaps.wall : bitmaps.floor;
            al_draw_bitmap(bitmap, i * BLOCK_SIZE, j * BLOCK_SIZE, 0);
        }
    }

    al_set_target_backbuffer(display);
}

bool Game::get_wall(int bx, int by)
{
    return map.walls[by * map.block_width + bx];
}

void Game::set_wall(int bx, int by, bool val)
{
    map.walls[by * map.block_width + bx] = val;
}
