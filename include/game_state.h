#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "bn_fixed.h"

// États du jeu
enum class GameState
{
    INTRO,
    MENU,
    PLAY,
    PAUSE,
    END,
    OPTIONS
};

// Structure pour les volumes
struct VolumeSettings
{
    int music;
    int menu_sfx;
    int game_music;
    int game_sfx;
    
    VolumeSettings() : music(10), menu_sfx(10), game_music(10), game_sfx(10) {}
};

// Structure pour l'état du gameplay
struct GameplayState
{
    int current_scene;
    bn::fixed camera_x;
    bn::fixed lapin_x;
    bn::fixed leopard_offset;
    int anim_counter;
    int anim_frame;
    
    GameplayState() : current_scene(0), camera_x(0), lapin_x(50), 
                      leopard_offset(150), anim_counter(0), anim_frame(0) {}
};

#endif
