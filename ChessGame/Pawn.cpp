#include "Pawn.h"

Pawn::Pawn(PieceType type, std::initializer_list<int> pos, bool is_white) : Piece(type, pos, is_white) {}

vector<position> Pawn::getMoves(vector<Piece> gameboard)
{
	vector<position> moves;

	// make sure we're not at the top edge of the board
	if (pos[1] < 7)
	{
		// is the square straight ahead occupied?
		Piece* piece_ptr1 = pieceAt(gameboard, { pos[0], pos[1] + 1 });
		if (piece_ptr1 == nullptr)
		{
			// square is unoccupied
			moves.push_back({ pos[0], pos[1] + 1});
		}
	}

	return moves;
}
