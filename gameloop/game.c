#include "game.h"

struct game new_game() {
    return (struct game) {
        .player    = init_player(),
        .camera    = init_follow_camera(),
        .terrain   = init_plane(),
        .obstacles = new_list(),
        .lives     = 3
    };
}

static inline void update_game_state(struct game* g) {
    player_move(&g->player);
    follow_player_cam(&g->camera, g->player);
    update_plane_position(g->player, &g->terrain);
}

static inline void render_3D_scene(struct game* g) {
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

static inline bool check_collisions(struct game* g) {
        if (g->obstacles.elements == 0) {
            return false;
        }
        if (CheckCollisionBoxes(get_bb(g->player),
            get_bb(g->obstacles.arr[0])) && 
            g->obstacles.arr[0].collided == false) {
                return true;
        }
        return false;
}

static inline void manage_collision(struct game* g) {
    g->obstacles.arr[0].color    = BLACK;
    g->obstacles.arr[0].collided = true;
    g->lives--;
}

static inline void manage_obstacles(struct game* g, int cycles) {
    if (should_obst_spawn(g->player, cycles)) {
        insert_element(&g->obstacles, create_obstacle(g->player));
    }
    if (should_obst_despawn(g->player, g->obstacles.arr[0])) {
        delete_element(&g->obstacles);
    }
}

static inline void reset_game(struct game* g) {
    g->player    = init_player();
    g->camera    = init_follow_camera();
    g->terrain   = init_plane();
    g->lives     = 3;
    reset_list(&g->obstacles);
}

static inline void draw_retry_screen(struct game* g) {
    DrawText("Press R to try again", 20, 20, 20, BLACK);
    if (IsKeyDown(KEY_R)) {
        reset_game(g);
    }
}

static inline void draw_ui(struct game* g) {
    if (g->lives > 0)
        DrawText(TextFormat("LIVES := %d", g->lives), 
            20, 20, 20, BLACK);
    else {
        draw_retry_screen(g);
    }
}

void run(struct game* g) {
    for (int cycles = 0; !WindowShouldClose(); cycles++) {
        // update game values
        if (g->lives > 0) {
            update_game_state(g);
            manage_obstacles(g, cycles);
            if (check_collisions(g)) {
                manage_collision(g);
            }
        }

        // draw on the screen
        BeginDrawing();
            ClearBackground(BEIGE);
            draw_ui(g);
            render_3D_scene(g);
        EndDrawing();
    }
}
