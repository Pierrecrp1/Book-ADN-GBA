#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "bn_fixed.h"

// Configuration des scènes
constexpr int SCENES_COUNT = 3;

// Position Y des sprites
constexpr bn::fixed Y_BOTTOM = 60;

// Limites de scroll
constexpr bn::fixed MAX_SCROLL_LEFT = 120;
constexpr bn::fixed MAX_SCROLL_RIGHT = -120;

// Limites de l'écran
constexpr bn::fixed SCREEN_EDGE_LEFT = -110;
constexpr bn::fixed SCREEN_EDGE_RIGHT = 110;

// Limites hors écran
constexpr bn::fixed OFF_SCREEN_LEFT = -130;
constexpr bn::fixed OFF_SCREEN_RIGHT = 130;

// Seuils de scroll
constexpr bn::fixed SCROLL_THRESHOLD_RIGHT = 96;
constexpr bn::fixed SCROLL_THRESHOLD_LEFT = -96;

// Positions initiales
constexpr bn::fixed LAPIN_START_X = 50;
constexpr bn::fixed LEOPARD_BASE_DISTANCE = 150;
constexpr bn::fixed LEOPARD_MIN_DISTANCE = 40;
constexpr bn::fixed DISTANCE_STEP = (LEOPARD_BASE_DISTANCE - LEOPARD_MIN_DISTANCE) / (SCENES_COUNT - 1);

// Vitesse de déplacement
constexpr bn::fixed MOVE_SPEED = 1;

#endif
