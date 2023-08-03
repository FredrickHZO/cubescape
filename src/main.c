#include <raylib.h>
#include "camera.h"
#include "cube.h"

const int SCREEN_HEIGHT = 700; 
const int SCREEN_WIDTH = 400;

int main(void) {
    Camera3D camera = init_camera();
    Vector3 pos     = {2.0f, 2.0f, 0};
    Vector3 size    = {2.0f, 2.0f, 2.0f};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cubescape");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        manage_camera_zoom(&camera);
        cube_move(&pos);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawCubeV(pos, size, RED);
                DrawCubeWiresV(pos, size, BLACK);
                DrawGrid(20, 10.0f);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
