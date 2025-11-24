#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include "game_state.h"

// Structure pour sauvegarder les données dans la SRAM
struct SaveData
{
    int volume_music;
    int volume_menu_sfx;
    int volume_game_music;
    int volume_game_sfx;
    int magic_number;
};

constexpr int SAVE_MAGIC = 0x424F4F4B; // "BOOK" en hexadécimal

class SaveManager
{
public:
    // Charger les volumes depuis la SRAM
    static VolumeSettings load_volumes();
    
    // Sauvegarder les volumes dans la SRAM
    static void save_volumes(const VolumeSettings& volumes);
};

#endif
