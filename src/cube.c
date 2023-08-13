#include "cube.h"

const float LATERAL_SPEED = 10.0f;
const float SPEED         = 20.0f;

// TODO: find a better and reliable way to randomly spawn enemies
const float EN_DIST_PLAYER = 15.0f;
const float DESPAWN_DIST   = 40.0f;
const int SPAWN_CYCLES     = 45;
const int SPAWN_OFFSET     = 2;
const int MIN_SIZE         = 2;
const int MAX_SIZE         = 5;

const int AVAILABLE_COLORS = 9;
const Color colors[] = {
    WHITE,   BLACK,
    GREEN,   BLUE, 
    MAGENTA, VIOLET,
    PURPLE,  ORANGE,
    GOLD,    PINK
};

cube init_cube() {
    return (cube){
        (Vector3){0, 0.5f, 0},
        (Vector3){1.0f, 1.0f, 1.0f},
        (Color)YELLOW,
    };
}

// checks if a new enemy should spawn during the session
int should_enemy_spawn(cube player, int cycles) {
    if (cycles % SPAWN_CYCLES == 0 && cycles != 0) {
            return true;
    } 
    return false;
}

// checks if an enemy should despawn after it's behind the player
int should_enemy_despawn(cube player, cube enemy) {
    if (player.pos.x > (enemy.pos.x) + DESPAWN_DIST) {
        return true;
    }
    return false;
}

// spawn an enemy with a random position and size
cube spawn_enemy(cube player) {
    cube enemy = {
        .pos = (Vector3){
            player.pos.x + EN_DIST_PLAYER,
            0.5f,
            GetRandomValue(
                -SPAWN_OFFSET,
                SPAWN_OFFSET
            )
        },
        .size = (Vector3){
            player.size.x,
            player.size.y,
            GetRandomValue(MIN_SIZE, MAX_SIZE)
        },
        .col = colors[GetRandomValue(0, AVAILABLE_COLORS)],
    };
    return enemy;
}

// draws to the screen the cube passed as input
void draw_cube(cube c) {
    DrawCubeV(c.pos, c.size, c.col); 
    DrawCubeWiresV(c.pos, c.size, BLACK);
}

// makes the cube go right
void move_cube_right(cube* c) {
    c->pos.z += LATERAL_SPEED * GetFrameTime();
}

// makes the cube go left
void move_cube_left(cube* c) {
    c->pos.z -= LATERAL_SPEED * GetFrameTime();
}

// automagically moves the cube forward and checks for
// lateral movement input from the player
void cube_move(cube* c) {
    c->pos.x += SPEED * GetFrameTime();
    if (IsKeyDown(KEY_A)) {
        move_cube_left(c);    
    }
    if (IsKeyDown(KEY_D)) {
        move_cube_right(c);
    }
}