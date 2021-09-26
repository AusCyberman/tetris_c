#include "block.h"
#include "raylib.h"
#include <game.h>
#include <stdio.h>
#include <stdlib.h>

void draw_grid(Vector2 starting_pos, unsigned int matrix_width,
               unsigned int matrix_height) {
  for (int i = 0; i < matrix_width; i++) {
    int x_pos = starting_pos.x + i * game.block_size;
    DrawLine(x_pos, 0, x_pos, starting_pos.y + game.block_size * matrix_height,
             BLACK);
  }
  for (int j = 0; j < matrix_height; j++) {
    int y_pos = starting_pos.y + j * game.block_size;
    DrawLine(0, y_pos, starting_pos.x + game.block_size * matrix_width, y_pos,
             BLACK);
  }
}

int main() {
  const int screenHeight = 800;
  const int screenWidth = 450;

  game_init(screenWidth, screenHeight, 20);

  Tetronimo *current_block = &game.current_block;

  *current_block = get_random_tetronimo((Vector2){0, 0});
  InitWindow(screenWidth, screenHeight, "Tetris");

  SetTargetFPS(10);

  while (!WindowShouldClose()) {
    BeginDrawing();
    draw_grid((Vector2){0, 0}, game.game_matrix.x, game.game_matrix.y);

    ClearBackground(RAYWHITE);
    tetronimo_display(current_block);
    if (tetronimo_update(current_block)) {
      for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
          if (!current_block->squares[y * 4 + x])
            continue;
          int index = ((current_block->location.y + y) * game.game_matrix.y +
                       current_block->location.x + x);
          game.matrix[index] = current_block->col;
        }
      }
      *current_block = get_random_tetronimo((Vector2){0, 0});
    }
    for (int x = 0; x < game.game_matrix.x; x++) {
      for (int y = 0; y < game.game_matrix.y; y++) {
        if (game.matrix[y * (int)game.game_matrix.y + x].a != 0)
          DrawRectangle(x * game.block_size, y * game.block_size,
                        game.block_size, game.block_size,
                        game.matrix[(y * (int)game.game_matrix.y) + x]);
      }
    }
    DrawFPS(10, 10);

    EndDrawing();
  }

  game_destroy();
  CloseWindow();
  return 0;
}
