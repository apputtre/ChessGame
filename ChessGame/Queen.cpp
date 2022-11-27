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

bool Queen::isLegalMove(position to_pos, Chessboard& board)
{
	if (!Piece::isLegalMove(to_pos, board))
		return false;

	// get our position
	position my_pos = board.getPosOf(this);

	// which diagonal are we on (rank - file)?
	int diagonal = my_pos[1] - my_pos[0];

	// which anit-diagonal are we on (rank + file)?
	int anti_diagonal = my_pos[1] + my_pos[0];

	// do we share a row, column, or diagonal with the destination?
	if (my_pos[0] == to_pos[0] || my_pos[1] == to_pos[1] || to_pos[1] - to_pos[0] == diagonal || to_pos[1] + to_pos[0] == anti_diagonal)
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
	}

	error_flags |= ILLEGAL_SQUARE;
	return false;
}