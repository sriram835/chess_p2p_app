/*

This header contains the definition for chess_board class, this class owns the
chess pieces class (Composition) and also keeps track of moves, verifies
validity of moves and provides an interface for renderer and p2p function to
make moves.

*/

#pragma once

#include "chess_piece.hpp"
#include <vector>

struct Move {
  Chess_piece *piece;
  int next_row;
  int next_col;
  int curr_col;
  int curr_row;
  bool color;
};


class Chess_board {
private:
  Chess_piece board[8][8];
  bool is_valid_move(struct Move move);
  bool is_valid_pawn_move(struct Move move);
  vector<Move> move_record;

public:
  Chess_board();
  bool make_move(int piece_type, int curr_col, int curr_row, int prev_col,
                 int prev_row);
  const Chess_piece (*get_board() const)[8] { return board; }
};




extern Chess_board board;
