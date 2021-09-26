#include "game.h"
#include <raymath.h>
#include <stdlib.h>
#include <string.h>

Game game;

int game_init(unsigned int game_width, unsigned int game_height,
              unsigned int block_size) {
  game.game_matrix.x = game_width / block_size;
  game.game_matrix.y = game_height / block_size;
  game.count = 0;
  game.block_size = block_size;
  game.game_size = Vector2Scale(game.game_matrix, block_size);
  game.matrix = calloc(game.game_matrix.x * game.game_matrix.y, sizeof(Color));
  memset(game.matrix, 0,
         game.game_matrix.x * game.game_matrix.y * sizeof(Color));
}

void game_destroy() { free(game.matrix); }
