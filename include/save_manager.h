#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include "game_state.h"

// Structure to save data in SRAM
struct SaveData
{
    int volume_music;
    int volume_menu_sfx;
    int volume_game_music;
    int volume_game_sfx;
    int magic_number;
};

constexpr int SAVE_MAGIC = 0x424F4F4B; // "BOOK" in hexadecimal

class SaveManager
{
public:
    // Load volumes from SRAM
    static VolumeSettings load_volumes();
    
    // Save volumes to SRAM
    static void save_volumes(const VolumeSettings& volumes);
};

#endif
