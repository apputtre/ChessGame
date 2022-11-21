#include "Queen.h"

Queen::Queen(PlayerColor color) : Piece(QUEEN, color) {}

vector<move> Queen::getMoves(Chessboard& board)
{
	vector<move> moves;
	vector<move> diagonals = check_diagonals(board);
	vector<move> cardinals = check_cardinals(board);

	moves.insert(moves.end(), diagonals.begin(), diagonals.end());
	moves.insert(moves.end(), cardinals.begin(), cardinals.end());

	return moves;
}