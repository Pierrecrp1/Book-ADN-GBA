#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include "bn_sprite_text_generator.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "game_state.h"

class MenuRenderer
{
public:
    // Generate a simple menu with integrated cursor
    static void render_simple_menu(
        bn::sprite_text_generator& text_gen,
        bn::vector<bn::sprite_ptr, 64>& text_sprites,
        const char* title,
        const char* const* options,
        int option_count,
        int selection,
        int title_y = -50,
        int first_option_y = -10,
        int option_spacing = 20
    );
    
    // Generate OPTIONS menu with volumes
    static void render_options_menu(
        bn::sprite_text_generator& text_gen,
        bn::vector<bn::sprite_ptr, 64>& text_sprites,
        const VolumeSettings& volumes,
        int selection
    );
};

#endif
