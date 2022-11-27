#include "Pawn.h"

Pawn::Pawn(PlayerColor color) : Piece(PAWN, color) {}

std::vector<move> Pawn::getMoves(Chessboard& board)
{
	return Piece::getMoves(board);
}

bool Pawn::isLegalMove(position pos_to, Chessboard& board)
{
	// check if the square is obstructed or off the board
	if (!Piece::isLegalMove(pos_to, board))
		return false;

	// get our position
	position my_pos = board.getPosOf(this);

	// which direction is forward?
	int forward_dir = (getColor() == WHITE ? 1 : -1);

	// is this a forward move (same column)?
	if (pos_to[0] == my_pos[0])
	{
		// is this a single-square forward move?
		if (pos_to[1] == my_pos[1] + forward_dir)
			// is the square empty?
			if (is_square_obstructed(board, pos_to))
			{
				error_flags |= OBSTRUCTED_SQUARE;
				return false;
			}
			else
				return true;
		// is this a double move?
		if (pos_to[1] == my_pos[1] + 2 * forward_dir && board.getPieceAt(pos_to) == nullptr)
			if (!has_moved)
				return true;
			else
			{
				error_flags |= NOT_FIRST_TURN;
				return false;
			}
	}

	// is this a diagonal move?
	if (abs(pos_to[0] - my_pos[0]) == 1 && pos_to[1] == my_pos[1] + forward_dir )
	{
		// get the piece at the destination square (if any)
		Piece* to_piece = board.getPieceAt(pos_to);
		// is this a capture?
		if (to_piece != nullptr)
			return true;
		else
		{
			error_flags |= ILLEGAL_SQUARE;
			return false;
		}
	}

	error_flags |= ILLEGAL_SQUARE;
	return false;
}
