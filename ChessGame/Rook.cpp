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

	// castling?


	// get our position
	position my_pos = board.getPosOf(this);

	// do we share a row / col with the destination square?
	if (my_pos[0] == to_pos[0] || my_pos[1] == to_pos[1])
	{
		position dir = (to_pos - my_pos).normalize();
		position to_check = my_pos + dir;
		Piece* target;
		while (to_check != (to_pos + dir))
		{
			target = board.getPieceAt(to_check);

			if (target != nullptr)
			{
				if (target->getColor() == getColor())
				{
					error_flags |= OBSTRUCTED_PATH;
					return false;
				}
				else
				{
					if (to_check != to_pos)
					{
						error_flags |= OBSTRUCTED_PATH;
						return false;
					}
				}
			}

			to_check += dir;
		}

		return true;
	}

	error_flags |= ILLEGAL_SQUARE;
	return false;
}