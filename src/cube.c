#include "cube.h"

const float SPEED = 10.0f;

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