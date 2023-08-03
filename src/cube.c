#include "cube.h"

void move_cube_right(Vector3* pos) {
    pos->z += 1.0f;
}

void move_cube_left(Vector3* pos) {
    pos->z -= 1.0f;
}

void cube_move(Vector3* pos) {
    if (IsKeyDown(KEY_A)) move_cube_left(pos);    
    if (IsKeyDown(KEY_D)) move_cube_right(pos);
}