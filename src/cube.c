#include "cube.h"

const float SPEED = 7.0f;

void move_cube_right(Vector3* pos) {
    pos->z += SPEED * GetFrameTime();
}

void move_cube_left(Vector3* pos) {
    pos->z -= SPEED * GetFrameTime();
}

void cube_move(Vector3* pos) {
    if (IsKeyDown(KEY_A)) move_cube_left(pos);    
    if (IsKeyDown(KEY_D)) move_cube_right(pos);
}

void auto_move_forward(Vector3* pos) {
    pos->x -= SPEED * GetFrameTime();
}

void random_spawn_cube(Vector3* pos) {
    
}