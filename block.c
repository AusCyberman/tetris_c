#include "block.h"
#include "game.h"

#define MAKE_BLOCK_CONSTRUCT(type_name, m0, m1, m2, m3, m4, m5, m6, m7, m8,    \
                             m9, m10, m11, m12, m13, m14, m15, color)          \
  Tetronimo construct_##type_name(Vector2 pos) {                               \
    Tetronimo block = (Tetronimo){Type##type_name,                             \
                                  {m0, m1, m2, m3, m4, m5, m6, m7, m8, m9,     \
                                   m10, m11, m12, m13, m14, m15},              \
                                  color,                                       \
                                  pos};                                        \
    return block;                                                              \
  }

MAKE_BLOCK_CONSTRUCT(I, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
                     (((Color){0, 255, 255, 255})))

MAKE_BLOCK_CONSTRUCT(J, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     (((Color){0, 0, 255, 255})))
MAKE_BLOCK_CONSTRUCT(L, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     (((Color){255, 165, 0, 255})))

MAKE_BLOCK_CONSTRUCT(O, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     (((Color){255, 255, 0, 255})))

MAKE_BLOCK_CONSTRUCT(S, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     (((Color){0, 255, 0, 255})))

MAKE_BLOCK_CONSTRUCT(Z, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     (((Color){255, 0, 255, 255})))

#undef MAKE_BLOCK_CONSTRUCT

typedef Tetronimo (*BlockConstructor)(Vector2 pos);

static BlockConstructor blocks[] = {construct_I, construct_J, construct_L,
                                    construct_O, construct_S, construct_Z};

Tetronimo get_random_tetronimo(Vector2 starting_loc) {
  int i = GetRandomValue(0, 5);

  return blocks[i](starting_loc);
}

int collide_tetronimo(Tetronimo *block, int new_x, int new_y) {
  int return_status = 0;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      int square = block->squares[y * 4 + x];
      if (square) {
        Vector2 ac_loc = Vector2Add((Vector2){new_x, new_y}, (Vector2){x, y});
        if (game.matrix[(int)(ac_loc.y * game.game_matrix.y + ac_loc.x)].a !=
            0) {
          if (ac_loc.y > block->location.y + y &&
              ac_loc.x - block->location.x != 0) {
            return 2;
          }
          return_status = 1;
        }
      }
    }
  }
  return return_status;
}

void tetronimo_display(Tetronimo *block) {
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      int square = block->squares[y * 4 + x];
      if (!square)
        continue;
      int ac_x = block->location.x * game.block_size + (x * game.block_size);
      int ac_y = block->location.y * game.block_size + (y * game.block_size);
      DrawRectangle(ac_x, ac_y, game.block_size, game.block_size, block->col);
    }
  }
}
int tetronimo_update(Tetronimo *block) {
  int new_x = block->location.x;
  int new_y = block->location.y;
  if (IsKeyDown(KEY_RIGHT))
    new_x += 1;
  if (IsKeyDown(KEY_LEFT))
    new_x -= 1;
  new_x = Clamp(new_x, 0, game.game_matrix.x - tetronimo_width(block));
  game.count++;
  if (game.count > 3) {

    new_y += 1;
    game.count = 0;
  }
  if (new_y >= game.game_matrix.y) {
    return 1;
  }
  switch (collide_tetronimo(block, new_x, new_y)) {
  case 1:
    return 0;
  case 2:
    return 1;
  default:
    break;
  }
  block->location.x = new_x;
  block->location.y = new_y;

  return 0;
}

unsigned int tetronimo_width(Tetronimo *block) {
  int max_width = 0;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (!block->squares[y * 4 + x]) {
        max_width = max_width < (x + 1) ? (x + 1) : max_width;
      }
    }
  }
  return max_width;
}

unsigned int tetronimo_height(Tetronimo *block) {
  int max_height = 0;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (!block->squares[y * 4 + x]) {
        max_height = max_height < (y + 1) ? (y + 1) : max_height;
      }
    }
  }
  return max_height;
}
