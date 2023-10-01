#pragma once
#include <cube.h>
#include <camera.h>
#include <list.h>

struct game {
    struct cube player;
    struct cube obstacle;
    struct cube terrain;
    Camera3D camera;
    list obstacles;
    int lives;
    float points;
};


struct game new_game();
void run(struct game* g);
