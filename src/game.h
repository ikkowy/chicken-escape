/* Copyright (C) 2021 Chicken Escape authors */

#pragma once

#include <vector>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define BLOCK_SIZE 64

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

    struct {
        bool lookleft = false;
        int lifepoints = 5;
        int x, y;
        int maze_x = 96, maze_y = 96;
        int speed = 4;
    } chicken;

    struct map {
        int block_width, block_height;
        int pixel_width, pixel_height;
        float redundancy;
        std::vector<bool> walls;
        ALLEGRO_BITMAP *bitmap;
        int x = 0, y = 0;   
    } map;
    
    

    bool running = true;
    bool redraw = false;

    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;

    struct {
        ALLEGRO_BITMAP *chicken;
        ALLEGRO_BITMAP *floor;
        ALLEGRO_BITMAP *wall;
    } bitmaps;

    void create_map(int bw, int bh, float redundancy);
    void build_maze();
    void draw_map();
    bool get_wall(int bx, int by);
    void set_wall(int bx, int by, bool val = true);
    
    /* Sound Design*/
    bool is_mute;
    ALLEGRO_SAMPLE* bgMusic;
    ALLEGRO_SAMPLE* sfxWalk;

    ALLEGRO_SAMPLE_INSTANCE* bgMusicInstance;
    ALLEGRO_SAMPLE_INSTANCE* sfxWalkInstance;

    unsigned int bgMusicPosition;
    unsigned int sfxWalkPosition;

    void init_audio();
    void setup_music();
    void play_music();
    void sfx_walk(bool mov);
    void control_audio();
    void control_music_volume(int vol);

    float musicVolume;
    float sfxVolume;
    ALLEGRO_KEYBOARD_STATE keyboard_state;
};
