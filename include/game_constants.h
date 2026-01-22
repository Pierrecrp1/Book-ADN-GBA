#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "bn_fixed.h"

// Configuration des scènes
constexpr int SCENES_COUNT = 10;

// Position Y des sprites
constexpr bn::fixed Y_BOTTOM = 60;

// Limites de scroll (images 320x160)
// Scroll max: 320 - 240 = 80px (40px on each side)
constexpr bn::fixed MAX_SCROLL_LEFT = 40;
constexpr bn::fixed MAX_SCROLL_RIGHT = -40;

// Screen limits (adjusted for 320px width)
constexpr bn::fixed SCREEN_EDGE_LEFT = -160;
constexpr bn::fixed SCREEN_EDGE_RIGHT = 160;

// Off-screen limits (scene transition)
constexpr bn::fixed OFF_SCREEN_LEFT = -170;
constexpr bn::fixed OFF_SCREEN_RIGHT = 170;

// Seuils de scroll (50% de SCREEN_EDGE pour transition fluide)
constexpr bn::fixed SCROLL_THRESHOLD_RIGHT = 80;
constexpr bn::fixed SCROLL_THRESHOLD_LEFT = -80;

// Positions initiales
constexpr bn::fixed LAPIN_START_X = 50;
constexpr bn::fixed LEOPARD_BASE_DISTANCE = 150;
constexpr bn::fixed LEOPARD_MIN_DISTANCE = 70;
constexpr bn::fixed DISTANCE_STEP = (LEOPARD_BASE_DISTANCE - LEOPARD_MIN_DISTANCE) / (SCENES_COUNT - 1);

constexpr bn::fixed LEOPARD_Y_OFFSET = 15;
constexpr bn::fixed BUNNY_Y_OFFSET = 0;

// Vitesse de déplacement
constexpr bn::fixed MOVE_SPEED = 1.5;

#endif
