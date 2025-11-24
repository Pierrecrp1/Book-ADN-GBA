#include "menu_renderer.h"
#include "bn_string.h"

void MenuRenderer::render_simple_menu(
    bn::sprite_text_generator& text_gen,
    bn::vector<bn::sprite_ptr, 64>& text_sprites,
    const char* title,
    const char* const* options,
    int option_count,
    int selection,
    int title_y,
    int first_option_y,
    int option_spacing)
{
    // Titre
    text_gen.generate(0, title_y, title, text_sprites);
    
    // Options avec curseur
    for(int i = 0; i < option_count; i++)
    {
        bn::string<32> option_text;
        if(i == selection)
        {
            option_text = "> ";
        }
        else
        {
            option_text = "  ";
        }
        option_text += options[i];
        
        int y = first_option_y + (i * option_spacing);
        text_gen.generate(0, y, option_text, text_sprites);
    }
    
    // Instructions
    text_gen.generate(0, 60, "Use UP/DOWN and A", text_sprites);
}

void MenuRenderer::render_options_menu(
    bn::sprite_text_generator& text_gen,
    bn::vector<bn::sprite_ptr, 64>& text_sprites,
    const VolumeSettings& volumes,
    int selection)
{
    text_gen.generate(0, -70, "OPTIONS", text_sprites);
    
    // Menu Music
    bn::string<32> music_text;
    if(selection == 0) music_text = "> Menu Music: ";
    else music_text = "  Menu Music: ";
    music_text += bn::to_string<4>(volumes.music);
    text_gen.generate(0, -40, music_text, text_sprites);
    
    // Menu SFX
    bn::string<32> menu_sfx_text;
    if(selection == 1) menu_sfx_text = "> Menu SFX: ";
    else menu_sfx_text = "  Menu SFX: ";
    menu_sfx_text += bn::to_string<4>(volumes.menu_sfx);
    text_gen.generate(0, -20, menu_sfx_text, text_sprites);
    
    // Game Music
    bn::string<32> game_music_text;
    if(selection == 2) game_music_text = "> Game Music: ";
    else game_music_text = "  Game Music: ";
    game_music_text += bn::to_string<4>(volumes.game_music);
    text_gen.generate(0, 0, game_music_text, text_sprites);
    
    // Game SFX
    bn::string<32> game_sfx_text;
    if(selection == 3) game_sfx_text = "> Game SFX: ";
    else game_sfx_text = "  Game SFX: ";
    game_sfx_text += bn::to_string<4>(volumes.game_sfx);
    text_gen.generate(0, 20, game_sfx_text, text_sprites);
    
    // BACK
    if(selection == 4) text_gen.generate(0, 40, "> BACK", text_sprites);
    else text_gen.generate(0, 40, "  BACK", text_sprites);
    
    // Instructions
    text_gen.generate(0, 65, "UP/DOWN LEFT/RIGHT A", text_sprites);
}
