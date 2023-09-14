#include "game.h"

struct game new_game() {
    return (struct game) {
        .player    = init_player(),
        .camera    = init_follow_camera(),
        .terrain   = init_plane(),
        .obstacles = new_list(),
        .lives = 3
    };
}

inline void update_game_state(struct game* g) {
        manage_camera_zoom(&g->camera);
        player_move(&g->player);
        follow_player_cam(&g->camera, g->player);
        update_plane_position(g->player, &g->terrain);
}

inline void render_3D_scene(struct game* g) {
    BeginMode3D(g->camera);
    if (g->obstacles.elements > 0) {
        for (int i = 0; i < g->obstacles.elements; i++) {
            draw_cube(g->obstacles.arr[i]);
        }
    }
    draw_plane(g->terrain);
    draw_cube(g->player);
    EndMode3D();
}

void run(struct game g) {
    for (int cycles = 0; !WindowShouldClose(); cycles++) {
        // update game values
        update_game_state(&g);

        if (should_obst_spawn(g.player, cycles)) {
            struct cube obstacle = create_obstacle(g.player);
            insert_element(&g.obstacles, obstacle);
        }
        if (should_obst_despawn(g.player, g.obstacles.arr[0])) {
            delete_element(&g.obstacles);
        }

        // draw on the screen
        BeginDrawing();
            ClearBackground(BEIGE);
            DrawText(TextFormat("z := %f", g.obstacles.arr[0].pos.z), 20, 20, 20, BLACK);
            render_3D_scene(&g);
        EndDrawing();
    }
}
