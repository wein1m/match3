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
bool matched[BOARD_SIZE][BOARD_SIZE];

Vector2 board_origin;

int score             = 0;
Vector2 selected_tile = {-1, -1};

char get_randomTile() {
  return tile_chars[rand() % TILE_TYPES];
}

bool find_matches() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      matched[y][x] = false;
    }
  }

  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE - 2; x++) {
      char t = board[y][x];
      if (t == board[y][x + 1] && t == board[y][x + 2]) {
        matched[y][x] = matched[y][x + 1] = matched[y][x + 2] = true;
        score += 10;
        return true;
      }
    }
  }

  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE - 2; y++) {
      char t = board[y][x];
      if (t == board[y + 1][x] && t == board[y + 2][x]) {
        matched[y][x] = matched[y + 1][x] = matched[y + 2][x] = true;
        score += 10;
        return true;
      }
    }
  }

  return false;
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

  Vector2 mouse_coord = {0, 0};

  while (!WindowShouldClose()) {

    // Get Selected Tile
    mouse_coord = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      float x = (mouse_coord.x - board_origin.x) / TILE_SIZE;
      float y = (mouse_coord.y - board_origin.y) / TILE_SIZE;

      if ((x >= 0 && x < BOARD_SIZE) && (y >= 0 && y < BOARD_SIZE)) {
        selected_tile = (Vector2){floor(x), floor(y)};
      }

      printf("%f, %f\n", x, y);
    }

    find_matches();

    BeginDrawing();
    ClearBackground(darkBlue);

    // Draw Board
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
          20, 1, 
          matched[y][x] == true ? GREEN : WHITE
        );
        // clang-format on
      }
    }

    // Draw Selected Tile
    if (selected_tile.x >= 0) {
      DrawRectangleLinesEx(
          (Rectangle){board_origin.x + (selected_tile.x * TILE_SIZE),
              board_origin.y + (selected_tile.y * TILE_SIZE),
              TILE_SIZE,
              TILE_SIZE},
          2,
          YELLOW);
    }

    // Draw Score
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

