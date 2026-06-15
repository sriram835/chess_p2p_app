/*

This file contains the methods used to render the chess board and take input
from user using raylib.

*/

#include "renderer.hpp"
#include "chess_board.hpp"
#include "consts.hpp"
#include <raylib.h>

void render_board(Chess_board board) {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  const Chess_piece(*board_ptr)[8] = board.get_board();

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {

      DrawRectangle(padding + col * cellW, padding + row * cellH, cellW - 2,
                    cellH - 2, WHITE);

      Chess_piece piece = board_ptr[row][col];

      Rectangle dest = {(float)padding + col * cellW + 10,
                        (float)padding + row * cellH + 10, cellW - 20,
                        cellH - 20};

      Texture2D texture;

      switch (piece.piece_type) {
      case pawn:
        texture = piece.color ? white_pawn_img : black_pawn_img;
        break;
      case rook:
        texture = piece.color ? white_rook_img : black_rook_img;
        break;
      case bishop:
        texture = piece.color ? white_bishop_img : black_bishop_img;
        break;
      case horse:
        texture = piece.color ? white_horse_img : black_horse_img;
        break;
      case queen:
        texture = piece.color ? white_queen_img : black_queen_img;
        break;
      case king:
        texture = piece.color ? white_king_img : black_king_img;
        break;
      default:
        continue;
      }

      Rectangle source = {0, 0, (float)texture.width, (float)texture.height};

      DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.0f, WHITE);
    }
  }
  EndDrawing();
}
