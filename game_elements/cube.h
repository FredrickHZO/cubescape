#pragma once
#include <raylib.h>

struct cube {
    Vector3 pos;
    Vector3 size;
    Color color;
    bool collided;
};

struct cube init_plane();
void draw_plane(struct cube p);
void update_plane_position(struct cube player, struct cube* plane);
struct cube init_player();
struct cube create_obstacle(struct cube player); 
void draw_cube(struct cube c); 
void player_move(struct cube* c);
int should_obst_spawn(struct cube player, int cycles);
int should_obst_despawn(struct cube player, struct cube enemy);