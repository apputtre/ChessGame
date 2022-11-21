#include "Bishop.h"

Bishop::Bishop(PlayerColor color) : Piece(BISHOP, color) {}

vector<move> Bishop::getMoves(Chessboard& board)
{
	vector<move> moves;
	vector<move> diagonals = check_diagonals(board);
	moves.insert(moves.end(), diagonals.begin(), diagonals.end());

	return moves;
}