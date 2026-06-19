
#include "chess_board.hpp"
#include "connection.hpp"
#include "consts.hpp"
#include "renderer.hpp"
#include <raylib.h>
#include <thread>

using namespace std;

Chess_board board;
Texture2D white_pawn_img;
Texture2D white_rook_img;
Texture2D white_bishop_img;
Texture2D white_horse_img;
Texture2D white_queen_img;
Texture2D white_king_img;

Texture2D black_pawn_img;
Texture2D black_rook_img;
Texture2D black_bishop_img;
Texture2D black_horse_img;
Texture2D black_queen_img;
Texture2D black_king_img;

int main() {
  InitWindow(screen_width, screen_height, "Game");
  white_pawn_img = LoadTexture("assets/white_pawn.png");
  white_rook_img = LoadTexture("assets/white_rook.png");
  white_bishop_img = LoadTexture("assets/white_bishop.png");
  white_horse_img = LoadTexture("assets/white_horse.png");
  white_queen_img = LoadTexture("assets/white_queen.png");
  white_king_img = LoadTexture("assets/white_king.png");

  black_pawn_img = LoadTexture("assets/black_pawn.png");
  black_rook_img = LoadTexture("assets/black_rook.png");
  black_bishop_img = LoadTexture("assets/black_bishop.png");
  black_horse_img = LoadTexture("assets/black_horse.png");
  black_queen_img = LoadTexture("assets/black_queen.png");
  black_king_img = LoadTexture("assets/black_king.png");

  thread conection_thread(connection);

  bool is_piece_selected = false;
  int selected_piece_row = -1;
  int selected_piece_col = -1;
  Vector2 mouse_pos;
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    render_board(board);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      mouse_pos = GetMousePosition();

      mouse_pos.x = mouse_pos.x - padding;
      mouse_pos.y = mouse_pos.y - padding;

      // cout << mouse_pos.x << " " << mouse_pos.y << "\n";

      if (mouse_pos.x >= 0 && mouse_pos.y >= 0) {
        if (mouse_pos.x <= cellW * 8 && mouse_pos.y <= cellH * 8) {

          int selected_col = mouse_pos.x / cellW;
          int selected_row = mouse_pos.y / cellH;

          // cout << selected_row << " " << selected_col << "\n";

          if (is_piece_selected) {
            board.make_move(
                board.get_board()[selected_piece_row][selected_piece_col]
                    .piece_type,
                selected_col, selected_row, selected_piece_col,
                selected_piece_row);
            is_piece_selected = false;

          } else {
            if (board.get_board()[selected_row][selected_col].piece_type ==
                -1) {
              continue;
            }
            selected_piece_row = selected_row;
            selected_piece_col = selected_col;
            is_piece_selected = true;
          }
        }
      }
    }
  }
  CloseWindow();
  return 0;
}
