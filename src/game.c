#include "game.h"

game new_game() {
    game cubescape = {
        .player  = init_cube(),
        .camera  = init_follow_camera(),
        .terrain = init_terrain(),
        .enemies = new_list()
    };
    return cubescape;
}

plane init_terrain() {
    return (plane) {
        (Vector3){100, 0, 0},
        (Vector2){400, 10},
        RED
    };
}

void draw_plane(game g) {
    // placeholder values
    DrawPlane(g.terrain.pos, g.terrain.size, g.terrain.color);
}

void change_plane_position(game* g) {
    if (g->player.pos.x > g->terrain.pos.x - 100) {
        g->terrain.pos.x += 50;
    }
}

// terrible implementation of enemy spawning system based on cycles
// TODO: replace it with something that is actually good and reliable
void run(game g) {
    int cycles = 0;
    while (!WindowShouldClose()) {
        manage_camera_zoom(&g.camera);
        cube_move(&g.player);
        follow_player_cam(&g.camera, g.player);

        BeginDrawing();
            ClearBackground(BEIGE);
            BeginMode3D(g.camera);
                change_plane_position(&g);
                if (should_enemy_spawn(g.player, cycles)) {
                        cube enemy = spawn_enemy(g.player);
                        insert_element(&g.enemies, enemy);
                }
                if (g.enemies.elements > 0) {
                    for (int i = 0; i < g.enemies.elements; i++) {
                        draw_cube(g.enemies.arr[i]);
                    }
                }
                if (should_enemy_despawn(g.player, g.enemies.arr[0])) {
                    delete_element(&g.enemies);
                }
                draw_cube(g.player);
                draw_plane(g);
                cycles += 1;
            EndMode3D();
        EndDrawing();
    }
}
