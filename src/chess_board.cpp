/*


The definition for Chess_board class methods are in this file.


*/

#include "chess_board.hpp"
#include "consts.hpp"
#include <iostream>

Chess_board::Chess_board() {
  for (int i = 0; i < 8; i++) {
    board[1][i] = Chess_piece(pawn, black, 1, i);
    board[6][i] = Chess_piece(pawn, white, 6, i);

    board[0][a] = Chess_piece(rook, black, 0, a);
    board[0][b] = Chess_piece(horse, black, 0, b);
    board[0][c] = Chess_piece(bishop, black, 0, c);
    board[0][d] = Chess_piece(queen, black, 0, d);
    board[0][e] = Chess_piece(king, black, 0, e);
    board[0][f] = Chess_piece(bishop, black, 0, f);
    board[0][g] = Chess_piece(horse, black, 0, g);
    board[0][h] = Chess_piece(rook, black, 0, h);

    board[7][a] = Chess_piece(rook, white, 7, a);
    board[7][b] = Chess_piece(horse, white, 7, b);
    board[7][c] = Chess_piece(bishop, white, 7, c);
    board[7][d] = Chess_piece(queen, white, 7, d);
    board[7][e] = Chess_piece(king, white, 7, e);
    board[7][f] = Chess_piece(bishop, white, 7, f);
    board[7][g] = Chess_piece(horse, white, 7, g);
    board[7][h] = Chess_piece(rook, white, 7, h);
  }
}

bool Chess_board::is_valid_move(struct Move move) {

  cout << "COLOR: " << move.color << " piece_type: " << move.piece->piece_type
       << "\n";

  if (move.piece->piece_type == -1) {
    cout << "PIECE type is -1\n";
    return false;
  }

  Chess_piece next_pos_piece = board[move.next_row][move.next_col];

  if (next_pos_piece.color == move.piece->color &&
      next_pos_piece.piece_type != -1) {

    cout << "tried to take piece of same color\n";
    return false;
  }

  if (move.next_col == move.curr_col && move.next_row == move.curr_row) {
    cout << "Tried to move a piece to the same position\n";
    return false;
  }

  switch (move.piece->piece_type) {

  case pawn:
    return is_valid_pawn_move(move);
    break;

  case rook:
    return is_valid_rook_move(move);
    break;
  }

  return false;
}

bool Chess_board::is_valid_pawn_move(struct Move move) {

  if (abs(move.curr_row - move.next_row) == 2 &&
      move.piece->is_first_move_done == true) {
    cout << "PAWN tried to move 2 steps, but first move is done\n";
    return false;
  }

  if (abs(move.curr_col - move.next_col) == 0 &&
      board[move.next_row][move.next_col].piece_type != -1) {

    cout << "Pawn tried to take piece directly in front\n";
    return false;
  }

  if (move.piece->color == white) {
    if (move.next_row - move.curr_row >= 0) {
      cout << "White pawn tried to move backwards\n";
      return false;
    }

    if (move.curr_col != move.next_col) {
      if (abs(move.curr_row - move.next_row) > 1 ||
          abs(move.curr_row - move.next_row) == 0) {
        cout << "White pawn moved more than one row or did not move when col "
                "is changed\n";
        return false;
      }

      if (board[move.next_row][move.next_col].piece_type == -1) {
        if (!move_record.empty()) {
          struct Move last_move = move_record.back();

          if (last_move.piece->piece_type != pawn) {
            return false;
          }

          if (last_move.next_col != last_move.curr_col) {

            return false;
          }

          if (abs(last_move.curr_row - last_move.next_row) != 2) {
            return false;
          }

          if (last_move.next_col != move.next_col) {

            return false;
          }

          if (last_move.next_row != move.curr_row) {

            return false;
          }
        } else {

          return false;
        }
      }

    } else {
      if (abs(move.curr_row - move.next_row) > 2 ||
          abs(move.curr_row - move.next_row) == 0) {
        cout << "White pawn moved more than 2 rows or did not move at all\n";
        return false;
      }
    }

  } else {

    if (move.next_row - move.curr_row <= 0) {
      return false;
    }

    if (move.curr_col != move.next_col) {
      if (abs(move.curr_row - move.next_row) > 1 ||
          abs(move.curr_row - move.next_row) == 0) {
        return false;
      }

    } else {
      if (abs(move.curr_row - move.next_row) > 2 ||
          abs(move.curr_row - move.next_row) == 0) {
        return false;
      }
    }
  }

  return true;
}

bool Chess_board::make_move(int piece_type, int curr_col, int curr_row,
                            int prev_col, int prev_row) {

  /*
  cout << "CURR_COL: " << curr_col << "\n";
  cout << "CURR_ROW: " << curr_row<< "\n";
  cout << "PREV_COL: " << prev_col<< "\n";
  cout << "PREV_ROW: " << prev_row<< "\n";
  */

  struct Move move;
  Chess_piece piece = board[prev_row][prev_col];

  move.piece = &piece;
  move.color = piece.color;
  move.curr_col = prev_col;
  move.curr_row = prev_row;
  move.next_col = curr_col;
  move.next_row = curr_row;

  if (!is_valid_move(move)) {
    cout << "INVALID MOVE\n";
    return false;
  }

  piece.position = {curr_row, curr_col};
  piece.is_first_move_done = true;
  move_record.push_back(move);

  board[curr_row][curr_col] = piece;
  board[prev_row][prev_col] = Chess_piece();

  return true;
}

bool Chess_board::is_valid_rook_move(struct Move move) {

  if (abs(move.curr_col - move.next_col) > 0 &&
      abs(move.curr_row - move.next_row) > 0) {
    cout << "Rook tried to move diagonally\n";
    return false;
  }

  if (abs(move.next_col - move.curr_col) > 0) {

    if (move.next_col > move.curr_col) {
      for (int col = move.curr_col + 1; col < move.next_col; col++) {
        if (board[move.curr_row][col].piece_type != -1) {
          cout << "Rook tried to move over a piece\n";
          return false;
        }
      }

    } else {
      for (int col = move.curr_col - 1; col > move.next_col; col--) {
        if (board[move.curr_row][col].piece_type != -1) {
          cout << "Rook tried to move over a piece\n";
          return false;
        }
      }
    }
  }

  if (abs(move.next_row - move.curr_row) > 0) {

    if (move.next_row > move.curr_row) {
      for (int row = move.curr_row + 1; row < move.next_row; row++) {
        if (board[row][move.curr_col].piece_type != -1) {
          cout << "Rook tried to move over a piece\n";
          return false;
        }
      }

    } else {
      for (int row = move.curr_row - 1; row > move.next_row; row--) {
        if (board[row][move.curr_col].piece_type != -1) {
          cout << "Rook tried to move over a piece\n";
          return false;
        }
      }
    }
  }
  return true;
}
