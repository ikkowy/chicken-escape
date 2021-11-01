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
        
    if(!al_reserve_samples(2))
        std::cout << "Reserve Sample Fail\n";
        
    setup_music();
}

void Game::setup_music()
{
    /* load music files */
    bgMusic = al_load_sample("scheming-weasel-faster.wav");
    sfxWalk = al_load_sample("footsteps.wav");
    
    if(!bgMusic)
        std::cout << "Couldn't load scheming weasel\n";
    if(!sfxWalk)
        std::cout << "Couldn't load footsteps\n";

    bgMusicInstance = al_create_sample_instance(bgMusic);
    sfxWalkInstance = al_create_sample_instance(sfxWalk);
    
    al_attach_sample_instance_to_mixer(bgMusicInstance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(sfxWalkInstance, al_get_default_mixer());
    
    al_set_sample_instance_playing(bgMusicInstance, true);
    al_set_sample_instance_playing(sfxWalkInstance, false);

    al_set_sample_instance_playmode(bgMusicInstance, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_playmode(sfxWalkInstance, ALLEGRO_PLAYMODE_LOOP);
    
    /* set parameters for chicken walk volume and speed */
    al_set_sample_instance_speed(sfxWalkInstance, 1.5);
    al_set_sample_instance_gain(sfxWalkInstance, 0.5);

    /* set initial values*/
    is_mute = true;
    bgMusicPosition = 0;
    musicVolume = 3.0;

    /* instructions */
    std::cout << "Press M to stop/start audio"<< std::endl;
    std::cout << "Press PGUP to increase music volume"<< std::endl;
    std::cout << "Press PGDN to decrease music volume" << std::endl;
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

void Game::sfx_walk(bool mov)
{
    switch(mov)
    {
        case true: 
            al_set_sample_instance_position(sfxWalkInstance, sfxWalkPosition);
            al_set_sample_instance_playing(sfxWalkInstance, true);
            break;
        case false:
            bgMusicPosition = al_get_sample_instance_position(sfxWalkInstance);
            al_set_sample_instance_playing(sfxWalkInstance, false);
            break;
    }
}

void Game::control_music_volume(int vol)
{
    switch(vol){
    case 1:
        if (musicVolume == 0) break;
        else {musicVolume -= 1.0; }
        break;
    case 2:
        if (musicVolume == 10.0) break;
        else {musicVolume += 1.0; }
        break;
    }
    al_set_sample_instance_gain(bgMusicInstance, musicVolume);
    musicVolume = al_get_sample_instance_gain(bgMusicInstance);
    std::cout << "Music volume: " << musicVolume << std::endl;

}
