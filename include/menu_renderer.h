#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include "bn_sprite_text_generator.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "game_state.h"

class MenuRenderer
{
public:
    // Générer un menu simple avec curseur intégré
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
    
    // Générer le menu OPTIONS avec volumes
    static void render_options_menu(
        bn::sprite_text_generator& text_gen,
        bn::vector<bn::sprite_ptr, 64>& text_sprites,
        const VolumeSettings& volumes,
        int selection
    );
};

#endif
