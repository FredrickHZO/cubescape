#pragma once
#include <raylib.h>

Camera3D init_camera();
void manage_camera_zoom(Camera3D* camera);
void follow_player_cam(Camera3D* camera, Vector3* p_pos);