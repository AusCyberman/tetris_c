#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"

typedef enum {
  TypeI,
  TypeJ,
  TypeK,
  TypeL,
  TypeO,
  TypeS,
  TypeT,
  TypeZ
} BlockType;

typedef struct {
  BlockType type;
  bool squares[4 * 4];
  Color col;
  Vector2 location;
  unsigned int width;

} Tetronimo;

typedef struct {
  size_t size;
  size_t length;
  Tetronimo *block;
} TetronimoList;

Tetronimo construct_I(Vector2 pos);
Tetronimo construct_J(Vector2 pos);
Tetronimo construct_L(Vector2 pos);
Tetronimo construct_O(Vector2 pos);
Tetronimo construct_S(Vector2 pos);
Tetronimo construct_Z(Vector2 pos);

Tetronimo get_random_tetronimo(Vector2 pos);
void tetronimo_display(Tetronimo *piece);
int tetronimo_update(Tetronimo *block);
unsigned int tetronimo_width(Tetronimo *block);
unsigned int tetronimo_height(Tetronimo *block);

#endif
