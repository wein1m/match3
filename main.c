#include "raylib.h"
#include <math.h>
#include <stdlib.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5

const char tile_chars[TILE_TYPES] = {'#', '@', '$', '%', '&'};

char board[BOARD_SIZE][BOARD_SIZE];

char get_randomTile() { return tile_chars[rand() % TILE_TYPES]; }

void init_board() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = get_randomTile();
    }
  }
}

int main() { return 0; }
