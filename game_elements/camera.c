#include "camera.h"

const float DEF_FOV = 40.0f;

const float CAMERA_X_POS = 2.0f;
const float CAMERA_Y_POS = 2.0f;
const float PLAYER_DISTANCE = 5.0f;
const float TARGET_DISTANCE = 1.0f;

Camera3D init_follow_camera() {
    return (Camera3D) {
        .position   = (Vector3){ CAMERA_X_POS, CAMERA_Y_POS, 0 },
        .target     = (Vector3){0},
        .up         = (Vector3){ 0.0f, 1.0f, 0.0f },
        .fovy       = DEF_FOV,
        .projection = CAMERA_PERSPECTIVE,
    };
}

void follow_player_cam(Camera3D* camera, struct cube c) {
    camera->target.x = c.pos.x + TARGET_DISTANCE;
    camera->position.x = c.pos.x - PLAYER_DISTANCE;
} 