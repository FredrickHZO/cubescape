#pragma once
#include <raylib.h>

typedef struct cube {
    Vector3 pos;
    Vector3 size;
    Color col;
    BoundingBox collision;
} cube;

cube init_plane();
void draw_plane(cube p);
void update_plane_position(cube player, cube* plane);
cube init_player();
cube create_obstacle(cube player); 
void draw_cube(cube c); 
void player_move(cube* c);
int should_obst_spawn(cube player, int cycles);
int should_obst_despawn(cube player, cube enemy);