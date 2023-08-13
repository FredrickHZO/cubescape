#pragma once
#include "../game_elements/cube.h"
#include "../game_elements/camera.h"
#include "../game_elements/plane.h"
#include "../utility/list.h"

typedef struct game {
    cube player;
    Camera3D camera;
    cube obstacle;
    list enemies;
    plane terrain;
    int lives;
    float points;
    double time;
} game;


game new_game();
void run(game g);
