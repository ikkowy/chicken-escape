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
        
    setup_music();
}

void Game::setup_music()
{
    /* load music files */
    bgMusic = al_load_sample("scheming-weasel-faster.wav");
    if(!bgMusic)
        std::cout << "Couldn't load scheming weasel\n";

    bgMusicInstance = al_create_sample_instance(bgMusic);
    al_attach_sample_instance_to_mixer(bgMusicInstance, al_get_default_mixer());
    
    al_set_sample_instance_playing(bgMusicInstance, true);
    al_set_sample_instance_playmode(bgMusicInstance, ALLEGRO_PLAYMODE_LOOP);

    /* set initial values*/
    is_mute = true;
    bgMusicPosition = 0;
    volume = 3.0;

    /* instructions */
    std::cout << "Press M to stop/start audio"<< std::endl;
    std::cout << "Press PGUP to increase volume"<< std::endl;
    std::cout << "Press PGDN to decrease volume" << std::endl;
}

void Game::play_music()
{
    al_set_sample_instance_position(bgMusicInstance, bgMusicPosition);
    al_set_sample_instance_playing(bgMusicInstance, true);
    is_mute = false;
}

void Game::control_audio()
{
    if(is_mute) play_music();
    else 
    {
        bgMusicPosition = al_get_sample_instance_position(bgMusicInstance);
        al_set_sample_instance_playing(bgMusicInstance, false);
        is_mute = true;
    }
}

void Game::control_music_volume(int vol)
{
    switch(vol){
    case 1:
        if (volume == 0) break;
        else {volume -= 1.0; }
        break;
    case 2:
        if (volume == 10.0) break;
        else {volume += 1.0; }
        break;
    }
    al_set_sample_instance_gain(bgMusicInstance, volume);
    volume = al_get_sample_instance_gain(bgMusicInstance);
    std::cout << "Volume: " << volume << std::endl;

}
