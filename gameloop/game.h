#pragma once
#include <cube.h>
#include <camera.h>
#include <list.h>

typedef struct game {
    cube player;
    Camera3D camera;
    cube obstacle;
    list obstacles;
    cube terrain;
    int lives;
    float points;
} game;


game new_game();
void run(game g);
