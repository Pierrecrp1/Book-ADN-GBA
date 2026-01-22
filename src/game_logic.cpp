#include "game_logic.h"
#include "game_constants.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_scene_01.h"
#include "bn_regular_bg_items_scene_02.h"
#include "bn_regular_bg_items_scene_03.h"
#include "bn_regular_bg_items_scene_04.h"
#include "bn_regular_bg_items_scene_05.h"
#include "bn_regular_bg_items_scene_06.h"
#include "bn_regular_bg_items_scene_07.h"
#include "bn_regular_bg_items_scene_08.h"
#include "bn_regular_bg_items_scene_09.h"
#include "bn_regular_bg_items_scene_10.h"
#include "bn_music_items.h"
#include "bn_sound_items.h"
#include "audio_manager.h"
#include "bn_sprite_items_bunny.h"
#include "bn_sprite_items_cheetah.h"
#include "bn_sprite_tiles_ptr.h"

void GameLogic::handle_scene_transition(GameplayState& gameplay, bn::optional<bn::regular_bg_ptr>& bg,
                                       VolumeSettings& volumes, bn::optional<bn::music_item>& current_music)
{
    (void)volumes;
    (void)current_music;
    
    // Free previous background
    bg.reset();
    
    // Charge le background de la scène actuelle
    switch(gameplay.current_scene)
    {
        case 0:
            bg = bn::regular_bg_items::scene_01.create_bg(0, 0);
            break;
        case 1:
            bg = bn::regular_bg_items::scene_02.create_bg(0, 0);
            break;
        case 2:
            bg = bn::regular_bg_items::scene_03.create_bg(0, 0);
            break;
        case 3:
            bg = bn::regular_bg_items::scene_04.create_bg(0, 0);
            break;
        case 4:
            bg = bn::regular_bg_items::scene_05.create_bg(0, 0);
            break;
        case 5:
            bg = bn::regular_bg_items::scene_06.create_bg(0, 0);
            break;
        case 6:
            bg = bn::regular_bg_items::scene_07.create_bg(0, 0);
            break;
        case 7:
            bg = bn::regular_bg_items::scene_08.create_bg(0, 0);
            break;
        case 8:
            bg = bn::regular_bg_items::scene_09.create_bg(0, 0);
            break;
        case 9:
            bg = bn::regular_bg_items::scene_10.create_bg(0, 0);
            break;
        default:
            break;
    }
    
    if(bg)
        bg->set_priority(3);
}

GameState GameLogic::update_gameplay(GameplayState& gameplay, bn::optional<bn::sprite_ptr>& lapin,
                                     bn::optional<bn::sprite_ptr>& leopard, bn::optional<bn::regular_bg_ptr>& bg,
                                     bool& moving_right, bool& moving_left, VolumeSettings& volumes,
                                     bn::optional<bn::music_item>& current_music)
{
    // Mouvement à droite
    if(bn::keypad::right_held())
    {
        moving_right = true;
        gameplay.facing_left = false;

        if(gameplay.lapin_x >= SCROLL_THRESHOLD_RIGHT && gameplay.camera_x > MAX_SCROLL_RIGHT)
        {
            gameplay.camera_x -= MOVE_SPEED;
            if(gameplay.camera_x < MAX_SCROLL_RIGHT)
                gameplay.camera_x = MAX_SCROLL_RIGHT;
        }
        else
        {
            gameplay.lapin_x += MOVE_SPEED;

            if(gameplay.current_scene == SCENES_COUNT - 1)
            {
                if(gameplay.lapin_x > SCREEN_EDGE_RIGHT)
                {
                    gameplay.lapin_x = SCREEN_EDGE_RIGHT;
                    return GameState::END;
                }
            }
            else if(gameplay.lapin_x >= OFF_SCREEN_RIGHT)
            {
                gameplay.current_scene++;
                gameplay.camera_x = MAX_SCROLL_LEFT;
                gameplay.lapin_x = SCREEN_EDGE_LEFT + 100;
                handle_scene_transition(gameplay, bg, volumes, current_music);
            }
        }
    }
    // Mouvement à gauche
    else if(bn::keypad::left_held())
    {
        moving_left = true;
        gameplay.facing_left = true;
        bn::fixed leopard_x = gameplay.lapin_x - gameplay.leopard_offset;

        if(leopard_x <= SCROLL_THRESHOLD_LEFT && gameplay.camera_x < MAX_SCROLL_LEFT)
        {
            gameplay.camera_x += MOVE_SPEED;
            if(gameplay.camera_x > MAX_SCROLL_LEFT)
                gameplay.camera_x = MAX_SCROLL_LEFT;
        }
        else
        {
            gameplay.lapin_x -= MOVE_SPEED;
            leopard_x = gameplay.lapin_x - gameplay.leopard_offset;

            if(gameplay.current_scene == 0)
            {
                if(leopard_x < SCREEN_EDGE_LEFT)
                {
                    gameplay.lapin_x = SCREEN_EDGE_LEFT + gameplay.leopard_offset;
                }
            }
            else if(leopard_x <= OFF_SCREEN_LEFT)
            {
                gameplay.current_scene--;
                gameplay.camera_x = MAX_SCROLL_RIGHT;
                gameplay.lapin_x = SCREEN_EDGE_RIGHT - 20;
                handle_scene_transition(gameplay, bg, volumes, current_music);
            }
        }
    }

    // Appliquer le scroll
    if(bg)
        bg->set_x(gameplay.camera_x);

    // Calculate cheetah/leopard offset
    gameplay.leopard_offset = LEOPARD_BASE_DISTANCE - (bn::fixed(gameplay.current_scene) * DISTANCE_STEP);
    bn::fixed leopard_x = gameplay.lapin_x - gameplay.leopard_offset;

    // Mettre à jour les positions
    if(lapin && leopard)
    {
        lapin->set_position(gameplay.lapin_x, Y_BOTTOM - BUNNY_Y_OFFSET);
        leopard->set_position(leopard_x, Y_BOTTOM - LEOPARD_Y_OFFSET);

        // Flip selon direction
        // lapin->set_horizontal_flip(moving_left);
        // leopard->set_horizontal_flip(moving_left);

        lapin->set_horizontal_flip(gameplay.facing_left);
        leopard->set_horizontal_flip(gameplay.facing_left);

        const bool is_moving = moving_right || moving_left;

        if(is_moving)
        {
            gameplay.anim_counter++;

            // Change frame toutes les 8 updates (à ajuster)
            if(gameplay.anim_counter >= 8)
            {
                gameplay.anim_counter = 0;
                gameplay.anim_frame = (gameplay.anim_frame + 1) % 8; // 8 frames !

                // IMPORTANT: on applique la frame via les tiles
                lapin->set_tiles(bn::sprite_items::bunny.tiles_item().create_tiles(gameplay.anim_frame));
                leopard->set_tiles(bn::sprite_items::cheetah.tiles_item().create_tiles(gameplay.anim_frame));

                // AudioManager::play_sound(bn::sound_items::animal_step, volumes.game_sfx);
            }
        }
        else
        {
            gameplay.anim_counter = 0;
            gameplay.anim_frame = 0;

            lapin->set_tiles(bn::sprite_items::bunny.tiles_item().create_tiles(0));
            leopard->set_tiles(bn::sprite_items::cheetah.tiles_item().create_tiles(0));
        }
    }

    return GameState::PLAY;
}
