#include "MLX/mlx.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

typedef struct s_player {
    int x;
    int y;
    int size;
    int color;
    double angle;
} t_player;


void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sign_x = x1 < x2 ? 1 : -1;
    int sign_y = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    mlx_pixel_put(mlx_ptr, win_ptr, x2, y2, color);

    while (x1 != x2 || y1 != y2) {
        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);
        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x1 += sign_x;
        }

        if (err2 < dx) {
            err += dx;
            y1 += sign_y;
        }
    }
}

void draw_player(t_player *player, void *mlx_ptr, void *win_ptr) {
    int half_size = player->size / 2;
    int top_left_x = player->x - half_size;
    int top_left_y = player->y - half_size;
    int bottom_right_x = player->x + half_size;
    int bottom_right_y = player->y + half_size;

    mlx_string_put(mlx_ptr, win_ptr, player->x, player->y, 0xFFFFFF, "");

    draw_line(mlx_ptr, win_ptr, player->x, player->y, player->x + 50 * cos(player->angle), player->y - 50 * sin(player->angle), 0xFFFFFF);
}
int key_press(int keycode, t_player *player) {
    int speed = 5;

    // if (keycode == 53)
    //     exit(0);

    if (keycode == 13)
        player->y -= speed;
    if (keycode == 1)
        player->y += speed;
    if (keycode == 2)
        player->x += speed;
    if (keycode == 0)
        player->x -= speed;

    if (keycode == 123) // Left arrow key
        player->angle -= 0.1;
    if (keycode == 124) // Right arrow key
        player->angle += 0.1;

    return 0;
}

int main() {
    void *mlx_ptr;
    void *win_ptr;
    t_player player;

    player.x = 200;  // Initial position
    player.y = 200;
    player.size = 30; // Size of the player
    player.color = 0xFF0000; // Red color (0xRRGGBB format)
    player.angle = 0; // Initial angle

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Player Movement Example");

    // Set up event handling for keyboard input
    mlx_hook(win_ptr, 2, 1L<<0, key_press, &player);

    // Main loop (rendering is handled here)
    while (1) {
        mlx_clear_window(mlx_ptr, win_ptr);

        // Draw the player and the line at its current position
        draw_player(&player, mlx_ptr, win_ptr);

        mlx_do_sync(mlx_ptr); // Update the window
    }

    mlx_loop(mlx_ptr);
    return 0;
}
