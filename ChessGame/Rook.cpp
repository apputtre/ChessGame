#include "Rook.h"

Rook::Rook(PlayerColor color) : Piece(ROOK, color) {}

vector<move> Rook::getMoves(Chessboard& board)
{
	vector<move> moves;
	vector<move> cardinals = check_cardinals(board);

	moves.insert(moves.end(), cardinals.begin(), cardinals.end());

	return moves;
}

bool Rook::isLegalMove(position to_pos, Chessboard& board)
{
	if (!Piece::isLegalMove(to_pos, board))
		return false;

	
}