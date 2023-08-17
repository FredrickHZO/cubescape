#include "cube.h"
#include <stdlib.h>

const float LATERAL_SPEED = 10.0f;
const float SPEED         = 20.0f;

// TODO: find a better and reliable way to randomly spawn enemies
const float DIST_FROM_PLAYER = 100.0f;
const float DESPAWN_DIST     = 40.0f;
const int SPAWN_CYCLES       = 35;
const int SPAWN_OFFSET       = 2;
const int MIN_SIZE           = 2;
const int MAX_SIZE           = 5;

const float TERRAIN_ELEVATION = -0.5f;
const float TERRAIN_LENGTH    = 900.0f;
const float TERRAIN_WIDTH     = 10.0f;
const float TERRAIN_PADDING   = 0.5f;

const int AVAILABLE_COLORS = 9;
const Color colors[] = {
    WHITE,   BLACK,
    GREEN,   BLUE, 
    MAGENTA, VIOLET,
    PURPLE,  ORANGE,
    GOLD,    PINK
};

// terrain related code
cube init_plane() {
    cube p = {
        .pos  = (Vector3){0, TERRAIN_ELEVATION, 0},
        .size = (Vector3){TERRAIN_LENGTH, 0.1f, TERRAIN_WIDTH},
        .col  = RED
    };
    return p;
}

float random_float(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

void draw_plane(cube p) {
    DrawCubeV(p.pos, p.size, p.col);
}

void update_plane_position(cube player, cube* plane) {
    if (player.pos.x > plane->pos.x - DIST_FROM_PLAYER) {
        plane->pos.x += DIST_FROM_PLAYER;
    }
}

// player related code
cube init_player() {
    cube p = {
        .pos  = (Vector3){0, 0.5f, 0},
        .size = (Vector3){1.0f, 1.0f, 1.0f},
        .col  = YELLOW
    };
    return p;
}

// draws to the screen the cube passed as input
void draw_cube(cube c) {
    DrawCubeV(c.pos, c.size, c.col); 
    DrawCubeWiresV(c.pos, c.size, BLACK);
}

// makes the cube go right
void move_player_right(cube* c) {
    c->pos.z += LATERAL_SPEED * GetFrameTime();
}

// makes the cube go left
void move_player_left(cube* c) {
    c->pos.z -= LATERAL_SPEED * GetFrameTime();
}

// automagically moves the cube forward and checks for
// lateral movement input from the player
void player_move(cube* c) {
    c->pos.x += SPEED * GetFrameTime();
    if (IsKeyDown(KEY_A)) {
        move_player_left(c);    
    }
    if (IsKeyDown(KEY_D)) {
        move_player_right(c);
    }
}

// Obstacle related code
// checks if a new enemy should spawn during the session
int should_obst_spawn(cube player, int cycles) {
    if (cycles % SPAWN_CYCLES == 0) {
            return true;
    } 
    return false;
}

// checks if an enemy should despawn after it's behind the player
int should_obst_despawn(cube player, cube enemy) {
    if (player.pos.x > (enemy.pos.x) + DESPAWN_DIST) {
        return true;
    }
    return false;
}


// spawn an enemy with a random position and size
cube create_obstacle(cube player) {
    int z_size = GetRandomValue(MIN_SIZE, MAX_SIZE);
    float z_pos = (TERRAIN_WIDTH / 2) - (z_size / 2);
    cube enemy = {
        .size = (Vector3){
            player.size.x,
            player.size.y,
            z_size
        },
        .pos = (Vector3){
            player.pos.x + DIST_FROM_PLAYER,
            0,
            random_float(
                (-z_pos) + TERRAIN_PADDING, 
                z_pos - TERRAIN_PADDING
            )
        },
        .col = colors[GetRandomValue(0, AVAILABLE_COLORS)],
    };
    return enemy;
}

