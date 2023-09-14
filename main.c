#include "gameloop/game.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720; 

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cubescape");
    SetTargetFPS(60);

        struct game cubescape = new_game();
        run(cubescape);

    CloseWindow();
}
