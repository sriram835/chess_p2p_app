/*


The definition for Chess_board class methods are in this file.


*/

#include "chess_board.hpp"
#include "consts.hpp"

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
