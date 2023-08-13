#include "plane.h"

plane init_terrain() {
    plane p = {
        .pos   = (Vector3){100, 0, 0},
        .size  = (Vector2){400, 10},
        .color = RED
    };
    return p;
}

void draw_plane(plane p) {
    // placeholder values
    DrawPlane(p.pos, p.size, p.color);
}

void change_plane_position(cube c, plane* p) {
    if (c.pos.x > p->pos.x - 100) {
        p->pos.x += 50;
    }
}