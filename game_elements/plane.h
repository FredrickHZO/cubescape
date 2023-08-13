#pragma once
#include <raylib.h>
#include "cube.h"

typedef struct plane {
    Vector3 pos;
    Vector2 size;
    Color color;
} plane;

plane init_terrain();
void draw_plane(plane p);
void change_plane_position(cube c, plane* p);