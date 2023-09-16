#pragma once
#include <cube.h>
#include <camera.h>
#include <list.h>

struct game {
    struct cube player;
    Camera3D camera;
    struct cube obstacle;
    list obstacles;
    struct cube terrain;
    int lives;
    float points;
};


struct game new_game();
void run(struct game* g);
