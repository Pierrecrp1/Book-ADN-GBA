#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "bn_sprite_ptr.h"
#include "bn_regular_bg_ptr.h"
#include "bn_optional.h"
#include "bn_fixed.h"
#include "bn_music_item.h"
#include "game_state.h"

class GameLogic
{
public:
    // Manage movement and gameplay logic
    static GameState update_gameplay(
        GameplayState& gameplay,
        bn::optional<bn::sprite_ptr>& lapin,
        bn::optional<bn::sprite_ptr>& leopard,
        bn::optional<bn::regular_bg_ptr>& bg,
        bool& moving_right,
        bool& moving_left,
        VolumeSettings& volumes,
        bn::optional<bn::music_item>& current_music
    );
    
    // Charger le background de la scène actuelle
    static void handle_scene_transition(
        GameplayState& gameplay,
        bn::optional<bn::regular_bg_ptr>& bg,
        VolumeSettings& volumes,
        bn::optional<bn::music_item>& current_music
    );
};

#endif
