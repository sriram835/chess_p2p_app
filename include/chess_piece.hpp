/*

This file contains the definition for Chess_piece class. This class would be
used to keep track of pieces states inside the chess board. One object of this
class will be created for one chess piece and Chess_board class owns the
chess_piece objects (Composition).
*/

#pragma once

using namespace std;

#include <stdexcept>
#include <utility>

class Chess_piece {
public:
  pair<int, int> position;
  bool color;
  int piece_type;
  bool is_first_move_done;
  Chess_piece()
      : position({0, 0}), color(false), piece_type(-1),
        is_first_move_done(false) {}
  Chess_piece(int type, bool color, int row, int col) {
    this->color = color;

    this->is_first_move_done = false;

    if ((col <= 7 && col >= 0) && (row <= 7 && row >= 0)) {
      this->position = {row, col};
    } else {
      throw runtime_error("Invalid Position");
    }

    if ((type >= 1 && type <= 6) || type == -1) {
      this->piece_type = type;
    } else {
      throw runtime_error("Invalid type");
    }
  }
};
