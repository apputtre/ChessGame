#include "Pawn.h"

Pawn::Pawn(PlayerColor color) : Piece(PAWN, color) {}

vector<move> Pawn::getMoves(chessboard& board)
{

	vector<move> moves;

	int forward_dir = ((color == WHITE) ? 1 : -1);

	// get our position
	position my_pos = board.findPiece(this);

	// can we move straight ahead?
	Piece* target = board[my_pos[0]][my_pos[1] + forward_dir];

	if (target == nullptr)
	{
		move m;
		m.piece = this;
		m.pos_from = my_pos;
		m.pos_to = { my_pos[0], my_pos[1] + forward_dir };

		moves.push_back(m);
	}

	/*
	// can we move to a diagonal square?
	// can we en passant?
	if (target->getColor() != color && !hasMoved) // e.g. is the target of opposing color & is this our first move?
	{
		if (pos[0] > 0)
			moves.push_back({ pos[0] - 1, pos[1] + forward_dir });
		if (pos[0] < 7)
			moves.push_back({ pos[0] + 1, pos[1] + forward_dir });
	}
	*/

	return moves;
}
