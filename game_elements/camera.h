#pragma once
#include <raylib.h>
#include "cube.h"

Camera3D init_follow_camera();
void manage_camera_zoom(Camera3D* camera);
void follow_player_cam(Camera3D* camera, struct cube c);