#include "raylib.h"

const int SCREEN_WIDTH = 450
const int SCREEN_HEIGHT = 800

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cubescape");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
}