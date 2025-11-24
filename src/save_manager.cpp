#include "save_manager.h"
#include "bn_sram.h"

VolumeSettings SaveManager::load_volumes()
{
    SaveData save;
    bn::sram::read(save);
    
    VolumeSettings volumes;
    
    if(save.magic_number == SAVE_MAGIC)
    {
        volumes.music = save.volume_music;
        volumes.menu_sfx = save.volume_menu_sfx;
        volumes.game_music = save.volume_game_music;
        volumes.game_sfx = save.volume_game_sfx;
    }
    
    return volumes;
}

void SaveManager::save_volumes(const VolumeSettings& volumes)
{
    SaveData save;
    save.volume_music = volumes.music;
    save.volume_menu_sfx = volumes.menu_sfx;
    save.volume_game_music = volumes.game_music;
    save.volume_game_sfx = volumes.game_sfx;
    save.magic_number = SAVE_MAGIC;
    
    bn::sram::write(save);
}
