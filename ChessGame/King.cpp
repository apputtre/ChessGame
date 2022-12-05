#include "King.h"

King::King(PlayerColor color) : Piece(KING, color) {}

vector<move> King::getMoves(Chessboard& board)
{
	vector<move> moves;

	position my_pos = board.getPosOf(this);

	position to_check;
	for (int i = 0; i < 8; i++) {
		to_check = my_pos + Directions[i];

		if (board.withinBounds(to_check))
		{
			Piece* target = board.getPieceAt(to_check);

			if (target == nullptr)
			{
				move m(this, my_pos, to_check);
				moves.push_back(m);
			}
			else if (target->getColor() != getColor())
			{
				move m(this, my_pos, to_check, board.getPieceAt(to_check));
				moves.push_back(m);
			}
		}
	}

	return moves;
}

bool King::isLegalMove(position to_pos, Chessboard& board)
{
	if (!Piece::isLegalMove(to_pos, board))
		return false;

	// get our position
	position my_pos = board.getPosOf(this);

	// castling?
	if (!has_moved && (to_pos == my_pos + East * 2 || to_pos == my_pos + West * 2))
	{

	}

	position diff = to_pos - my_pos;

	if (std::abs(diff[0]) <= 1 && std::abs(diff[1]) <= 1)
	{
		if (!is_square_obstructed(board, to_pos))
		{
			PlayerColor enemy_color = (getColor() == WHITE ? BLACK : WHITE);

			if (!is_square_threatened(board, to_pos, enemy_color))
			{
				return true;
			}
			else
			{
				error_flags |= ILLEGAL_SQUARE;
				return true;
			}
		}
		else
		{
			error_flags |= OBSTRUCTED_SQUARE;
			return false;
		}
	}

	error_flags |= ILLEGAL_SQUARE;
	return false;
}