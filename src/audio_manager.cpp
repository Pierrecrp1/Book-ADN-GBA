#include "audio_manager.h"
#include "bn_music.h"
#include "bn_music_items.h"
#include "bn_sound.h"
#include "bn_fixed.h"

void AudioManager::play_music(bn::music_item music, const VolumeSettings& volumes, bool is_game_music)
{
    if(bn::music::playing())
    {
        bn::music::stop();
    }
    
    music.play();
    
    int volume = is_game_music ? volumes.game_music : volumes.music;
    bn::music::set_volume(bn::fixed(volume) / 10);
}

void AudioManager::apply_volume(const bn::optional<bn::music_item>& current_music, const VolumeSettings& volumes)
{
    if(current_music)
    {
        if(current_music.value() == bn::music_items::menu_music)
        {
            bn::music::set_volume(bn::fixed(volumes.music) / 10);
        }
        else
        {
            bn::music::set_volume(bn::fixed(volumes.game_music) / 10);
        }
    }
}

void AudioManager::play_sound(const bn::sound_item& sound, int volume)
{
    sound.play(bn::fixed(volume) / 10);
}
