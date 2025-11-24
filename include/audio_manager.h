#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "bn_music_item.h"
#include "bn_sound_item.h"
#include "bn_optional.h"
#include "game_state.h"

class AudioManager
{
public:
    // Démarrer une musique avec le volume approprié
    static void play_music(bn::music_item music, const VolumeSettings& volumes, bool is_game_music);
    
    // Appliquer le volume à la musique en cours
    static void apply_volume(const bn::optional<bn::music_item>& current_music, const VolumeSettings& volumes);
    
    // Jouer un effet sonore
    static void play_sound(const bn::sound_item& sound, int volume);
};

#endif
