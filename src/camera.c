#include "camera.h"

const float MAX_FOV = 110.0f;
const float MIN_FOV = 80.0f;
const float DEF_FOV = 90.0f;

Camera3D init_camera() {
    return (Camera3D) {
        .position   = (Vector3){ 10.0f, 10.0f, 0 },
        .target     = (Vector3){ 0.0f, 0.0f, 0.0f },
        .up         = (Vector3){ 0.0f, 0.1f, 0.0f },
        .fovy       = DEF_FOV,
        .projection = CAMERA_PERSPECTIVE
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