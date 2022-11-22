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
			move m;
			Piece* target = board.getPieceAt(to_check);

			if (target == nullptr)
			{
				m.piece = this;
				m.pos_from = my_pos;
				m.pos_to = to_check;

				moves.push_back(m);
			}
			else if (target->getColor() != getColor())
			{
				m.piece = this;
				m.pos_from = my_pos;
				m.pos_to = to_check;
				m.capture = true;
				m.captured = target;

				moves.push_back(m);
			}
		}
	}

	return moves;
}