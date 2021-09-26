#ifndef GAME_H
#define GAME_H
#include <block.h>
typedef struct {
    Vector2 game_size;
    Vector2 game_matrix;
    unsigned int count;
    unsigned int block_size;
    unsigned int max_score;
    unsigned current_score;
    Tetronimo current_block;
    Tetronimo next_blocks[4];
    Color* matrix;
} Game;

extern Game game;

int game_init(unsigned int game_width, unsigned int game_height,unsigned int block_size);

void game_destroy();


#endif