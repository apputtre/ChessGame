#include "Bishop.h"

Bishop::Bishop(PlayerColor color) : Piece(BISHOP, color) {}

vector<move> Bishop::getMoves(Chessboard& board)
{
	vector<move> moves;
	vector<move> diagonals = check_diagonals(board);
	moves.insert(moves.end(), diagonals.begin(), diagonals.end());

	return moves;
}

bool Bishop::isLegalMove(position to_pos, Chessboard& board)
{
	if (!Piece::isLegalMove(to_pos, board))
		return false;

	// get our position
	position my_pos = board.getPosOf(this);

	// which diagonal are we on (rank - file)?
	int diagonal = my_pos[1] - my_pos[0];

	// which anit-diagonal are we on (rank + file)?
	int anti_diagonal = my_pos[1] + my_pos[0];

	// does the destination square share a diagonal with us?
	if (to_pos[1] - to_pos[0] == diagonal || to_pos[1] + to_pos[0] == anti_diagonal)
	{
		// check if there are any pieces between us and the destination square
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