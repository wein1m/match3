#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5

const char tile_chars[TILE_TYPES] = {'#', '@', '$', '%', '&'};

char board[BOARD_SIZE][BOARD_SIZE];

Vector2 board_origin;

int score = 0;

char get_randomTile() {
  return tile_chars[rand() % TILE_TYPES];
}

void init_board() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = get_randomTile();
    }
  }

  int board_width  = BOARD_SIZE * TILE_SIZE;
  int board_height = BOARD_SIZE * TILE_SIZE;

  // clang-format off
  board_origin = (Vector2) {
    (float)(GetScreenWidth() - board_width) / 2,
    (float)(GetScreenHeight() - board_height) / 2
  };
  // clang-format on
}

int main() {
  const int screenW = 800;
  const int screenH = 450;
  Color darkBlue    = {25, 11, 33, 255};

  InitWindow(screenW, screenH, "ASCII MATCH 3~");
  SetTargetFPS(60);
  srand(time(NULL)); // time(NULL) returns current time in seconds

  Font font_04b03 = LoadFont("assets/04b03.ttf");

  init_board();

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(darkBlue);

    for (int y = 0; y < BOARD_SIZE; y++) {
      for (int x = 0; x < BOARD_SIZE; x++) {
        // clang-format off
        Rectangle rect = {
          board_origin.x + (float)x * TILE_SIZE, 
          board_origin.y + (float)y * TILE_SIZE,
          TILE_SIZE, TILE_SIZE
        };

        DrawRectangleLinesEx(rect, 1, DARKGRAY);

        DrawTextEx(
          GetFontDefault(),
          TextFormat("%c", board[y][x]),
          (Vector2){rect.x + 15, rect.y + 11},
          20, 1, WHITE
        );
        // clang-format on
      }
    }

    DrawTextEx(font_04b03,
        TextFormat("score: %d", score),
        (Vector2){20, 20},
        24,
        1,
        YELLOW);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

