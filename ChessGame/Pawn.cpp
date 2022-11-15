#include "Pawn.h"

Pawn::Pawn(PieceType type, std::initializer_list<int> pos, PlayerColor color) : Piece(type, pos, color) {}

vector<position> Pawn::getMoves(vector<Piece*> &gameboard)
{
	int forward_dir = ((color == WHITE) ? 1 : -1);

	vector<position> moves;

	// make sure we're not at the top edge of the board
	if (pos[1] >= 7)
	{
		return moves;
	}

	Piece* target;

	// can we move straight ahead?
	target = pieceAt(gameboard, { pos[0], pos[1] + forward_dir });

	if (target == nullptr)
		moves.push_back({ pos[0], pos[1] + forward_dir });

	// can we move to a diagonal square?
	// can we en passant?
	if (target->getColor() != color && !hasMoved) // e.g. is the target of opposing color & is this our first move?
	{
		if (pos[0] > 0)
			moves.push_back({ pos[0] - 1, pos[1] + forward_dir });
		if (pos[0] < 7)
			moves.push_back({ pos[0] + 1, pos[1] + forward_dir });
	}

	return moves;
}
