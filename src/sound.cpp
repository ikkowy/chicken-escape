/* Copyright (C) 2021 Chicken Escape authors */

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>

#include "game.h"


// Music
/*Scheming Weasel (faster version) by Kevin MacLeod
Link: https://incompetech.filmmusic.io/song/4326-scheming-weasel-faster-version
License: https://filmmusic.io/standard-license*/
void Game::init_audio()
{
    //init
    if(!al_install_audio())
        std::cout << "Install Audio Fail\n";
        
    if(!al_init_acodec_addon())
        std::cout << "Init Acodec Fail\n";
        
    if(!al_reserve_samples(1))
        std::cout << "Reserve Sample Fail\n";

    is_mute = true;
    std::cout << "Press M to stop/start audio\n";
}

void Game::play_audio()
{
    bgMusic = al_load_sample("scheming-weasel-faster.wav");
    
    if(!bgMusic)
        std::cout << "Couldn't load sample\n";
        
    if(!al_play_sample(bgMusic, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL))
        std::cout << "Couldn't play sample\n";
        
    is_mute = false;
}

void Game::control_audio()
{
    if(is_mute) play_audio();
    else 
    {
        al_stop_samples();
        is_mute = true;
    }
}
