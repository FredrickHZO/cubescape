#pragma once
#include "cube.h"
#include "camera.h"
#include "list.h"

typedef struct plane {
    Vector3 pos;
    Vector2 size;
    Color color;
} plane;

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
plane init_terrain();