#include <raylib.h>
#include "camera.h"
#include "cube.h"

const int SCREEN_HEIGHT = 700; 
const int SCREEN_WIDTH = 400;

int main(void) {
    Camera3D camera = init_camera();
    Vector3 size    = {0.5f, 0.5f, 0.5f};
    Vector3 pos     = {0, size.y/2, 0};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cubescape");
    SetTargetFPS(60);

    float points = 1;

    while (!WindowShouldClose()) {
        manage_camera_zoom(&camera);
        cube_move(&pos);
        auto_move_forward(&pos);
        follow_player_cam(&camera, &pos);
        points += 0.5;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(TextFormat("Score: %.0f", points), 10, 10, 20, BEIGE);
            BeginMode3D(camera);
                DrawCubeV(pos, size, RED);
                DrawCubeWiresV(pos, size, BLACK);
                DrawPlane(
                    (Vector3){-100, 0, 0},
                    (Vector2){300, 5},
                    LIME
                );
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}
