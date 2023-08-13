#pragma once
#include <raylib.h>

typedef struct cube {
    Vector3 pos;
    Vector3 size;
    Color col;
    BoundingBox collision;
} cube;

cube init_cube();
cube spawn_enemy(cube player); 
void draw_cube(cube c); 
void cube_move(cube* c);
int should_enemy_spawn(cube player, int cycles);
int should_enemy_despawn(cube player, cube enemy);