/* Copyright (C) 2021 Chicken Escape authors */

#include <vector>

#include "game.h"

using std::vector;

struct point{
    int x,y;
};

void Game::create_map(int bw, int bh, float redundancy)
{
    switch (bw % 3)
    {
        case 0:
            bw = bw + 1;
            break;
        case 2:
            bw = bw + 2;
            break;
    }
    switch (bh % 3)
    {
        case 0:
            bh = bh + 1;
            break;
        case 2:
            bh = bh + 2;
            break;
    }
    map.block_width = bw;
    map.block_height = bh;
    map.pixel_width = map.block_width * BLOCK_SIZE;
    map.pixel_height = map.block_height * BLOCK_SIZE;
    map.bitmap = al_create_bitmap(map.pixel_width, map.pixel_height);
    map.walls = std::vector<bool>(map.block_width * map.block_height, 1);
    map.redundancy = redundancy;
}

void Game::build_maze()
{
    /*init vars*/
    int i, j, red_int;
    vector<point> neighbour_list, connected_neighbours, redundancy_walls;
    point start_point, cur_p, tmp_p;
    time_t nTime;

    /*set starting point*/
    start_point.x = 1;
    start_point.y = 1;
    neighbour_list.push_back(start_point);

    while (neighbour_list.size() > 0)
    {
        srand((unsigned) time(&nTime));
        /*choosing current point*/
        cur_p = neighbour_list.at(rand() % neighbour_list.size());
        if (get_wall(cur_p.x, cur_p.y))
        {
            /*sort neighbours*/
            connected_neighbours.clear();
            if (cur_p.x > 1)
            {
                tmp_p.x = cur_p.x - 3;
                tmp_p.y = cur_p.y;
                if (get_wall(tmp_p.x, tmp_p.y))
                {    
                    neighbour_list.push_back(tmp_p);
                }
                else
                {
                    connected_neighbours.push_back(tmp_p);
                }
            }
            if (cur_p.y > 1)
            {
                tmp_p.x = cur_p.x;
                tmp_p.y = cur_p.y - 3;
                if (get_wall(tmp_p.x, tmp_p.y))
                {    
                    neighbour_list.push_back(tmp_p);
                }
                else
                {
                    connected_neighbours.push_back(tmp_p);
                }
            }
            if (cur_p.x < map.block_width - 3)
            {
                tmp_p.x = cur_p.x + 3;
                tmp_p.y = cur_p.y;
                if (get_wall(tmp_p.x, tmp_p.y))
                {    
                    neighbour_list.push_back(tmp_p);
                }
                else
                {
                    connected_neighbours.push_back(tmp_p);
                }
            }
            if (cur_p.y < map.block_height - 3)
            {
                tmp_p.x = cur_p.x;
                tmp_p.y = cur_p.y + 3;
                if (get_wall(tmp_p.x, tmp_p.y))
                {    
                    neighbour_list.push_back(tmp_p);
                }
                else
                {
                    connected_neighbours.push_back(tmp_p);
                }
            }

            /*set current point as earth*/
            set_wall(cur_p.x, cur_p.y, 0);
            set_wall(cur_p.x + 1, cur_p.y, 0);
            set_wall(cur_p.x + 1, cur_p.y + 1, 0);
            set_wall(cur_p.x, cur_p.y + 1, 0);

            /*connect current point*/
            if (connected_neighbours.size() > 0)
            {
                tmp_p = connected_neighbours.at(rand() % connected_neighbours.size());
                if (tmp_p.x < cur_p.x)
                {
                    set_wall(cur_p.x - 1, cur_p.y, 0);
                    set_wall(cur_p.x - 1, cur_p.y + 1, 0);
                }
                else if (tmp_p.x > cur_p.x)
                {
                    set_wall(cur_p.x + 2, cur_p.y, 0);
                    set_wall(cur_p.x + 2, cur_p.y + 1, 0);
                }
                else if (tmp_p.y < cur_p.y)
                {
                    set_wall(cur_p.x, cur_p.y - 1, 0);
                    set_wall(cur_p.x + 1, cur_p.y - 1, 0);
                }
                else
                {
                    set_wall(cur_p.x, cur_p.y + 2, 0);
                    set_wall(cur_p.x + 1, cur_p.y + 2, 0);
                }
            }
        }

        /*delete current point from neighbour list*/
        i = neighbour_list.size() - 1;
        while (i >= 0)
        {
            tmp_p = neighbour_list.at(i);
            if (tmp_p.x == cur_p.x && tmp_p.y == cur_p.y)
            {
                neighbour_list.erase(neighbour_list.begin() + i);
            }
            i--;
        }
    }

    /*add redundancy*/
    if (map.redundancy > 0)
    {
        /*fill vector with walls*/
        i = 1;
        while (i < map.block_width - 1)
        {
            j = 3;
            while (j < map.block_height - 1)
            {
                tmp_p.x = i;
                tmp_p.y = j;
                if (get_wall(tmp_p.x, tmp_p.y))
                {
                    redundancy_walls.push_back(tmp_p);
                }
                j = j + 3;
            }
            i = i + 3;
        }
        i = 3;
        while (i < map.block_width - 1)
        {
            j = 1;
            while (j < map.block_height - 1)
            {
                tmp_p.x = i;
                tmp_p.y = j;
                if (get_wall(tmp_p.x, tmp_p.y))
                {
                    redundancy_walls.push_back(tmp_p);
                }
                j = j + 3;
            }
            i = i + 3;
        }


        red_int = map.redundancy * redundancy_walls.size();

        /*remove some walls*/
        for(red_int; red_int >= 0; red_int--)
        {
            cur_p = redundancy_walls.at(rand() % redundancy_walls.size());
            if (cur_p.x % 3 == 1)
            {
                set_wall(cur_p.x, cur_p.y, 0);
                set_wall(cur_p.x + 1, cur_p.y, 0);
            }
            else
            {
                set_wall(cur_p.x, cur_p.y, 0);
                set_wall(cur_p.x, cur_p.y + 1, 0);
            }

            /*remove removed wall from redundancy list*/
            i = redundancy_walls.size() - 1;
            while (i >= 0)
            {
                tmp_p = redundancy_walls.at(i);
                if (tmp_p.x == cur_p.x && tmp_p.y == cur_p.y)
                {
                    redundancy_walls.erase(redundancy_walls.begin() + i);
                }
                i--;
            }
        }

        /*remove columns*/
        for(i = 3; i < map.block_height - 1; i += 3)
        {
            for(j = 3; j < map.block_width - 1; j += 3)
            {
                if (!(get_wall(j-1,i) || get_wall(j,i-1) || get_wall(j+1,i) || get_wall(j,i+1)))
                {
                    set_wall(j,i,0);
                }
            }
        }
    }
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
