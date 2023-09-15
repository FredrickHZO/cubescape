#include "game.h"
#include <math.h>

struct game new_game() {
    return (struct game) {
        .player    = init_player(),
        .camera    = init_follow_camera(),
        .terrain   = init_plane(),
        .obstacles = new_list(),
        .lives = 3
    };
}

// bounding boxes forced my hand, collision aren't detected well unless i do this terribleness
static inline void update_enemy_hitboxes(struct game* g) {
    for (int i = 0; i < g->obstacles.elements; i++) {
        g->obstacles.arr[i].hitbox = (BoundingBox) {
            (Vector3) {
                g->obstacles.arr[i].pos.x - (g->obstacles.arr[i].size.x / 2),
                g->obstacles.arr[i].pos.y - (g->obstacles.arr[i].size.y / 2),
                g->obstacles.arr[i].pos.z - (g->obstacles.arr[i].size.z / 2)
            },
            (Vector3) {
                g->obstacles.arr[i].pos.x + (g->obstacles.arr[i].size.x / 2),
                g->obstacles.arr[i].pos.y + (g->obstacles.arr[i].size.y / 2),
                g->obstacles.arr[i].pos.z + (g->obstacles.arr[i].size.z / 2)
            },
        };
    }
}

static inline void update_game_state(struct game* g) {
        manage_camera_zoom(&g->camera);
        player_move(&g->player);
        follow_player_cam(&g->camera, g->player);
        update_plane_position(g->player, &g->terrain);
        update_enemy_hitboxes(g);
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

static inline void check_collisions(struct game* g) {
    if (CheckCollisionBoxes(g->player.hitbox, g->obstacles.arr[0].hitbox)
        && g->obstacles.arr[0].collided == false) {
            g->obstacles.arr[0].collided = true;
            g->lives--;
    }
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

        check_collisions(&g);

        // draw on the screen
        BeginDrawing();
            ClearBackground(BEIGE);
            DrawText(TextFormat("LIVES := %d", g.lives), 20, 20, 20, BLACK);
            render_3D_scene(&g);
        EndDrawing();
    }
}
