#include "camera.h"

const float MAX_FOV = 150.0f;
const float MIN_FOV = 80.0f;
const float DEF_FOV = 100.0f;

const float CAMERA_X_POS = 2.0f;
const float CAMERA_Y_POS = 2.5f;
const float PLAYER_DISTANCE = 3.0f;
const float TARGET_DISTANCE = 2.0f;

Camera3D init_follow_camera() {
    return (Camera3D) {
        .position   = (Vector3){ CAMERA_X_POS, CAMERA_Y_POS, 0 },
        .target     = (Vector3){0},
        .up         = (Vector3){ 0.0f, 1.0f, 0.0f },
        .fovy       = DEF_FOV,
        .projection = CAMERA_PERSPECTIVE,
    };
}

void cam_zoom_out(Camera3D* camera) {
    if (camera->fovy < MAX_FOV) camera->fovy += 1.0f;
}

void cam_zoom_in(Camera3D* camera) {
    if (camera->fovy > MIN_FOV) camera->fovy -= 1.0f;
}

void manage_camera_zoom(Camera3D* camera) {
    if (IsKeyDown(KEY_M)) cam_zoom_out(camera);
    if (IsKeyDown(KEY_J)) cam_zoom_in(camera);
}

void follow_player_cam(Camera3D* camera, cube c) {
    camera->target.x = c.pos.x + TARGET_DISTANCE;
    camera->position.x = c.pos.x - PLAYER_DISTANCE;
} 