#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_fixed.h"
#include "bn_vector.h"
#include "bn_sprite_text_generator.h"
#include "bn_music.h"
#include "bn_sound_items.h"
#include "bn_music_items.h"
#include "bn_sprite_tiles_ptr.h"

#include "common_variable_8x16_sprite_font.h"

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
#include "bn_regular_bg_items_final_scene.h"
#include "bn_sprite_items_bunny.h"
#include "bn_sprite_items_cheetah.h"

#include "game_state.h"
#include "game_constants.h"
#include "save_manager.h"
#include "audio_manager.h"
#include "menu_renderer.h"
#include "game_logic.h"

// Function to handle INTRO state
bool handle_intro_state(int& intro_counter, bn::vector<bn::sprite_ptr, 64>& text_sprites, 
                        bn::sprite_text_generator& text_generator)
{
    if(intro_counter == 0)
    {
        text_sprites.clear();
        text_generator.generate(0, -40, "BOOK ADN", text_sprites);
        text_generator.generate(0, 40, "Press A to skip", text_sprites);
    }
    
    intro_counter++;
    
    if(intro_counter > 180 || bn::keypad::a_pressed() || bn::keypad::start_pressed())
    {
        text_sprites.clear();
        return true; // Go to menu
    }
    
    return false;
}

// Function to handle MENU state
GameState handle_menu_state(int& menu_selection, bn::vector<bn::sprite_ptr, 64>& text_sprites,
                            bn::sprite_text_generator& text_generator, VolumeSettings& volumes,
                            bn::optional<bn::music_item>& current_music, GameplayState& gameplay)
{
    // Start menu music
    // if(!current_music || current_music.value() != bn::music_items::menu_music)
    // {
    //     current_music = bn::music_items::menu_music;
    //     AudioManager::play_music(bn::music_items::menu_music, volumes, false);
    // }

    // Unique background music that loops throughout the ROM
    // Only restart the music if it's not already playing
    if(!bn::music::playing())
    {
        current_music = bn::music_items::main_theme;
        AudioManager::play_music(bn::music_items::main_theme, volumes, false);
    }
    
    // Display the menu
    if(text_sprites.empty())
    {
        const char* options[] = {"PLAY", "OPTIONS", "QUIT"};
        MenuRenderer::render_simple_menu(text_generator, text_sprites, "BOOK ADN", 
                                        options, 3, menu_selection);
    }
    
    // Navigation
    if(bn::keypad::up_pressed() && menu_selection > 0)
    {
        menu_selection--;
        AudioManager::play_sound(bn::sound_items::menu_move, volumes.menu_sfx);
        text_sprites.clear();
        const char* options[] = {"PLAY", "OPTIONS", "QUIT"};
        MenuRenderer::render_simple_menu(text_generator, text_sprites, "BOOK ADN", 
                                        options, 3, menu_selection);
    }
    else if(bn::keypad::down_pressed() && menu_selection < 2)
    {
        menu_selection++;
        AudioManager::play_sound(bn::sound_items::menu_move, volumes.menu_sfx);
        text_sprites.clear();
        const char* options[] = {"PLAY", "OPTIONS", "QUIT"};
        MenuRenderer::render_simple_menu(text_generator, text_sprites, "BOOK ADN", 
                                        options, 3, menu_selection);
    }
    
    // Bouton B pour quitter
    if(bn::keypad::b_pressed())
    {
        return GameState::INTRO; // Quit signal (handled in main)
    }
    
    // Sélection
    if(bn::keypad::a_pressed())
    {
        AudioManager::play_sound(bn::sound_items::menu_select, volumes.menu_sfx);
        text_sprites.clear();
        
        if(menu_selection == 0) // PLAY
        {
            // Reset gameplay
            gameplay = GameplayState();
            return GameState::PLAY;
        }
        else if(menu_selection == 1) // OPTIONS
        {
            return GameState::OPTIONS;
        }
        else // QUIT
        {
            return GameState::INTRO; // Signal pour quitter
        }
    }
    
    return GameState::MENU;
}

// Function to handle PAUSE state
GameState handle_pause_state(int& pause_selection, bn::vector<bn::sprite_ptr, 64>& text_sprites,
                             bn::sprite_text_generator& text_generator, VolumeSettings& volumes,
                             GameState& previous_state)
{
    // Display pause menu
    if(text_sprites.empty())
    {
        const char* options[] = {"RESUME", "OPTIONS", "BACK TO MENU"};
        MenuRenderer::render_simple_menu(text_generator, text_sprites, "PAUSE",
                                        options, 3, pause_selection);
    }
    
    // Navigation
    if(bn::keypad::up_pressed() && pause_selection > 0)
    {
        pause_selection--;
        AudioManager::play_sound(bn::sound_items::menu_move, volumes.menu_sfx);
        text_sprites.clear();
        const char* options[] = {"RESUME", "OPTIONS", "BACK TO MENU"};
        MenuRenderer::render_simple_menu(text_generator, text_sprites, "PAUSE",
                                        options, 3, pause_selection);
    }
    else if(bn::keypad::down_pressed() && pause_selection < 2)
    {
        pause_selection++;
        AudioManager::play_sound(bn::sound_items::menu_move, volumes.menu_sfx);
        text_sprites.clear();
        const char* options[] = {"RESUME", "OPTIONS", "BACK TO MENU"};
        MenuRenderer::render_simple_menu(text_generator, text_sprites, "PAUSE",
                                        options, 3, pause_selection);
    }
    
    // Sélection
    if(bn::keypad::a_pressed())
    {
        AudioManager::play_sound(bn::sound_items::menu_select, volumes.menu_sfx);
        text_sprites.clear();
        
        if(pause_selection == 0) // RESUME
        {
            return previous_state;
        }
        else if(pause_selection == 1) // OPTIONS
        {
            previous_state = GameState::PAUSE;
            return GameState::OPTIONS;
        }
        else // BACK TO MENU
        {
            return GameState::MENU;
        }
    }
    
    // Start ou B pour fermer
    if(bn::keypad::start_pressed() || bn::keypad::b_pressed())
    {
        text_sprites.clear();
        return previous_state;
    }
    
    return GameState::PAUSE;
}

// Function to adjust volume and redraw the menu
void adjust_volume_and_redraw(int& volume, int delta, int selection,
                              bn::vector<bn::sprite_ptr, 64>& text_sprites,
                              bn::sprite_text_generator& text_generator,
                              VolumeSettings& volumes,
                              bn::optional<bn::music_item>& current_music)
{
    volume += delta;
    if(volume < 0) volume = 0;
    if(volume > 10) volume = 10;
    
    // Apply volume in real time
    AudioManager::apply_volume(current_music, volumes);
    
    // Save
    SaveManager::save_volumes(volumes);
    
    // Sound feedback
    AudioManager::play_sound(bn::sound_items::menu_move, volumes.menu_sfx);
    
    // Immediate redraw
    text_sprites.clear();
    MenuRenderer::render_options_menu(text_generator, text_sprites, volumes, selection);
}

// Function to handle OPTIONS state
GameState handle_options_state(int& options_selection, bn::vector<bn::sprite_ptr, 64>& text_sprites,
                               bn::sprite_text_generator& text_generator, VolumeSettings& volumes,
                               GameState& previous_state, bn::optional<bn::music_item>& current_music)
{
    // Display options menu
    if(text_sprites.empty())
    {
        MenuRenderer::render_options_menu(text_generator, text_sprites, volumes, options_selection);
    }
    
    // Navigation UP/DOWN
    if(bn::keypad::up_pressed() && options_selection > 0)
    {
        options_selection--;
        AudioManager::play_sound(bn::sound_items::menu_move, volumes.menu_sfx);
        text_sprites.clear();
        MenuRenderer::render_options_menu(text_generator, text_sprites, volumes, options_selection);
    }
    else if(bn::keypad::down_pressed() && options_selection < 3)
    {
        options_selection++;
        AudioManager::play_sound(bn::sound_items::menu_move, volumes.menu_sfx);
        text_sprites.clear();
        MenuRenderer::render_options_menu(text_generator, text_sprites, volumes, options_selection);
    }
    // Adjust volumes LEFT/RIGHT
    else if(bn::keypad::left_pressed())
    {
        if(options_selection == 0) adjust_volume_and_redraw(volumes.music, -1, options_selection, 
                                                            text_sprites, text_generator, volumes, current_music);
        else if(options_selection == 1) adjust_volume_and_redraw(volumes.menu_sfx, -1, options_selection,
                                                                 text_sprites, text_generator, volumes, current_music);
        // Game Music commented out - uses the same music as Menu Music
        // else if(options_selection == 2) adjust_volume_and_redraw(volumes.game_music, -1, options_selection,
        //                                                          text_sprites, text_generator, volumes, current_music);
        else if(options_selection == 2) adjust_volume_and_redraw(volumes.game_sfx, -1, options_selection,
                                                                 text_sprites, text_generator, volumes, current_music);
    }
    else if(bn::keypad::right_pressed())
    {
        if(options_selection == 0) adjust_volume_and_redraw(volumes.music, 1, options_selection,
                                                            text_sprites, text_generator, volumes, current_music);
        else if(options_selection == 1) adjust_volume_and_redraw(volumes.menu_sfx, 1, options_selection,
                                                                 text_sprites, text_generator, volumes, current_music);
        // Game Music commented out - uses the same music as Menu Music
        // else if(options_selection == 2) adjust_volume_and_redraw(volumes.game_music, 1, options_selection,
        //                                                          text_sprites, text_generator, volumes, current_music);
        else if(options_selection == 2) adjust_volume_and_redraw(volumes.game_sfx, 1, options_selection,
                                                                 text_sprites, text_generator, volumes, current_music);
    }
    
    // Return with A or B
    if((bn::keypad::a_pressed() && options_selection == 3) || bn::keypad::b_pressed())
    {
        AudioManager::play_sound(bn::sound_items::menu_select, volumes.menu_sfx);
        text_sprites.clear();
        
        if(previous_state == GameState::PAUSE)
        {
            previous_state = GameState::PLAY;
            return GameState::PAUSE;
        }
        else
        {
            return GameState::MENU;
        }
    }
    
    return GameState::OPTIONS;
}

int main()
{
    bn::core::init();
    
    // State variables
    GameState state = GameState::INTRO;
    GameState previous_state = GameState::INTRO;
    int intro_counter = 0;
    int menu_selection = 0;
    int pause_selection = 0;
    int options_selection = 0;
    
    // Load volumes
    VolumeSettings volumes = SaveManager::load_volumes();
    
    // Current music
    bn::optional<bn::music_item> current_music;
    
    // Gameplay state
    GameplayState gameplay;
    
    // Sprites and backgrounds
    bn::optional<bn::sprite_ptr> lapin;
    bn::optional<bn::sprite_ptr> leopard;
    bn::optional<bn::regular_bg_ptr> bg;
    
    // Text generator
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_center_alignment();
    bn::vector<bn::sprite_ptr, 64> text_sprites;
    
    while(true)
    {
        bool moving_right = false;
        bool moving_left = false;
        
        switch(state)
        {
            case GameState::INTRO:
            {
                if(handle_intro_state(intro_counter, text_sprites, text_generator))
                {
                    state = GameState::MENU;
                }
                break;
            }
            
            case GameState::MENU:
            {
                GameState next_state = handle_menu_state(menu_selection, text_sprites, text_generator,
                                                        volumes, current_music, gameplay);
                
                if(next_state == GameState::PLAY)
                {
                    // Start game music
                    // current_music = bn::music_items::scene_01_music;
                    // AudioManager::play_music(bn::music_items::scene_01_music, volumes, true);
                    
                    // Music already playing from menu, no need to restart it
                    // if(!bn::music::playing())
                    // {
                    //     current_music = bn::music_items::main_theme;
                    //     AudioManager::play_music(bn::music_items::main_theme, volumes, true);
                    // }
                    
                    // Reset gameplay to start from the left
                    gameplay = GameplayState();
                    
                    // Create background for scene 01
                    GameLogic::handle_scene_transition(gameplay, bg, volumes, current_music);
                    
                    lapin = bn::sprite_items::bunny.create_sprite(gameplay.lapin_x, Y_BOTTOM);
                    leopard = bn::sprite_items::cheetah.create_sprite(gameplay.lapin_x - gameplay.leopard_offset, Y_BOTTOM);

                    lapin->set_z_order(0);
                    leopard->set_z_order(0);

                    // Force frame 0 at start
                    lapin->set_tiles(bn::sprite_items::bunny.tiles_item().create_tiles(0));
                    leopard->set_tiles(bn::sprite_items::cheetah.tiles_item().create_tiles(0));

                }
                else if(next_state == GameState::INTRO) // Quit signal
                {
                    return 0;
                }
                
                state = next_state;
                break;
            }
            
            case GameState::PLAY:
            {
                // Check START for pause
                if(bn::keypad::start_pressed())
                {
                    previous_state = GameState::PLAY;
                    pause_selection = 0;
                    text_sprites.clear();
                    state = GameState::PAUSE;
                    break;
                }
                
                // Update gameplay
                GameState next_state = GameLogic::update_gameplay(gameplay, lapin, leopard, bg,
                                                                  moving_right, moving_left, volumes,
                                                                  current_music);
                
                if(next_state == GameState::END)
                {
                    text_sprites.clear();
                    state = GameState::END;
                }
                
                break;
            }
            
            case GameState::PAUSE:
            {
                state = handle_pause_state(pause_selection, text_sprites, text_generator,
                                          volumes, previous_state);
                
                if(state == GameState::MENU)
                {
                    // Destroy resources
                    lapin.reset();
                    leopard.reset();
                    bg.reset();
                    menu_selection = 0;
                }
                
                break;
            }
            
            case GameState::END:
            {
                if(text_sprites.empty())
                {
                    // End music
                    // current_music = bn::music_items::final_music;
                    // AudioManager::play_music(bn::music_items::final_music, volumes, true);

                    // Music already playing, no need to restart it
                    // if(!bn::music::playing())
                    // {
                    //     current_music = bn::music_items::main_theme;
                    //     AudioManager::play_music(bn::music_items::main_theme, volumes, true);
                    // }
                    
                    // End background
                    bg = bn::regular_bg_items::final_scene.create_bg(0, 0);
                    bg->set_priority(3);
                    
                    // Destroy bunny
                    lapin.reset();
                    
                    // Position leopard
                    if(leopard)
                    {
                        leopard->set_position(0, 0);
                        leopard->set_horizontal_flip(false);
                        leopard->set_rotation_angle(0);
                    }
                    
                    // Text
                    text_generator.generate(0, -60, "THE END", text_sprites);
                    text_generator.generate(0, -40, "The leopard caught", text_sprites);
                    text_generator.generate(0, -25, "the bunny!", text_sprites);
                    text_generator.generate(0, 45, "Press A to return", text_sprites);
                    text_generator.generate(0, 60, "to menu", text_sprites);
                }
                
                if(bn::keypad::a_pressed())
                {
                    AudioManager::play_sound(bn::sound_items::final_confirm, volumes.menu_sfx);
                    text_sprites.clear();
                    leopard.reset();
                    bg.reset();
                    menu_selection = 0;
                    state = GameState::MENU;
                }
                
                break;
            }
            
            case GameState::OPTIONS:
            {
                state = handle_options_state(options_selection, text_sprites, text_generator,
                                            volumes, previous_state, current_music);
                break;
            }
            
            default:
                break;
        }
        
        bn::core::update();
    }
}
