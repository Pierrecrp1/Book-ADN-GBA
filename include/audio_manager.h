#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "bn_music_item.h"
#include "bn_sound_item.h"
#include "bn_optional.h"
#include "game_state.h"

class AudioManager
{
public:
    // Start music with appropriate volume
    static void play_music(bn::music_item music, const VolumeSettings& volumes, bool is_game_music);
    
    // Apply volume to current music
    static void apply_volume(const bn::optional<bn::music_item>& current_music, const VolumeSettings& volumes);
    
    // Play a sound effect
    static void play_sound(const bn::sound_item& sound, int volume);
};

#endif
