#include "cube.h"
#include <stdlib.h>

const float LATERAL_SPEED = 10.0f;
const float SPEED         = 20.0f;
const float P_SIZE        = 0.5f;

const float DIST_FROM_PLAYER = 100.0f;
const float DESPAWN_DIST     = 1.5f;
const int SPAWN_CYCLES       = 30;
const float MIN_SIZE         = 1;
const float MAX_SIZE         = 3.5;

const float TERRAIN_ELEVATION = -0.25f;
const float TERRAIN_LENGTH    = 900.0f;
const float TERRAIN_WIDTH     = 5.0f;

const int AVAILABLE_COLORS = 8;
const Color colors[] = {
    WHITE, GREEN,
    MAGENTA, VIOLET,
    PURPLE,  ORANGE,
    GOLD,    PINK,
    BLUE
};

// terrain related code
struct cube init_plane() {
    return (struct cube) {
        .pos   = (Vector3){0, TERRAIN_ELEVATION, 0},
        .size  = (Vector3){TERRAIN_LENGTH, 0.1f, TERRAIN_WIDTH},
        .color = RED
    };
}

float random_float(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

void draw_plane(struct cube p) {
    DrawCubeV(p.pos, p.size, p.color);
}

void update_plane_position(struct cube player, struct cube* plane) {
    if (player.pos.x > plane->pos.x - DIST_FROM_PLAYER) {
        plane->pos.x += DIST_FROM_PLAYER;
    }
}

// player related code
struct cube init_player() {
    return (struct cube) {
        .pos   = (Vector3){0, TERRAIN_ELEVATION + P_SIZE, 0},
        .size  = (Vector3){P_SIZE, P_SIZE, P_SIZE},
        .color = YELLOW
    };
}

// draws to the screen the cube passed as input
void draw_cube(struct cube c) {
    DrawCubeV(c.pos, c.size, c.color); 
    DrawCubeWiresV(c.pos, c.size, BLACK);
}

// makes the cube go right
void move_player_right(struct cube* c) {
    c->pos.z += LATERAL_SPEED * GetFrameTime();
}

// makes the cube go left
void move_player_left(struct cube* c) {
    c->pos.z -= LATERAL_SPEED * GetFrameTime();
}

// automagically moves the cube forward and checks for
// lateral movement input from the player
void player_move(struct cube* c) {
    c->pos.x += SPEED * GetFrameTime();

    float target_pos = (TERRAIN_WIDTH / 2) - c->size.z;
    if (IsKeyDown(KEY_A)) {
        if (c->pos.z > -target_pos)
        move_player_left(c);    
    }
    if (IsKeyDown(KEY_D)) {
        if (c->pos.z < target_pos)
        move_player_right(c);
    }
}

// Obstacle related code
// checks if a new enemy should spawn during the session
int should_obst_spawn(struct cube player, int cycles) {
    if (cycles % SPAWN_CYCLES == 0) {
            return true;
    } 
    return false;
}

// checks if an enemy should despawn after it's behind the player
int should_obst_despawn(struct cube player, struct cube enemy) {
    if (player.pos.x > (enemy.pos.x) + DESPAWN_DIST) {
        return true;
    }
    return false;
}

BoundingBox get_bb(struct cube c) {
    return (BoundingBox){
        (Vector3) {
            c.pos.x - c.size.x / 2,
            c.pos.y - c.size.y / 2,
            c.pos.z - c.size.z / 2,
        },
        (Vector3) {
            c.pos.x + c.size.x / 2,
            c.pos.y + c.size.y / 2,
            c.pos.z + c.size.z / 2,
        },
    };
} 


// spawn an enemy with a random position and size
struct cube create_obstacle(struct cube player) {
    float z_size = random_float(MIN_SIZE, MAX_SIZE);
    float z_pos = (TERRAIN_WIDTH / 2) - (z_size / 2);

    float obst_x_pos = player.pos.x + DIST_FROM_PLAYER;
    float random_z = random_float(-z_pos, z_pos);

    return (struct cube) {
        .size = (Vector3){
            player.size.x,
            player.size.y,
            z_size
        },
        .pos = (Vector3){
            obst_x_pos,
            0,
            random_z
        },
        .color = colors[GetRandomValue(0, AVAILABLE_COLORS)],
        .collided = false
    };
}