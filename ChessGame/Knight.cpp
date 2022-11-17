#include "Knight.h"

Knight::Knight(PlayerColor color) : Piece(KNIGHT, color) {}

vector<move> Knight::getMoves(Chessboard& board)
{
	vector<move> moves;

	position my_pos = board.getPosOf(this);

	// squares to check
	position to_check[8] = {
		//northwest
		{my_pos[0] - 2, my_pos[1] + 1 },
		//north-northwest
		{ my_pos[0] - 1, my_pos[1] + 2 },
		//north-northeast
		{ my_pos[0] + 1, my_pos[1] + 2 },
		//northeast
		{ my_pos[0] + 2, my_pos[1] + 1 },
		//southeast
		{ my_pos[0] + 2, my_pos[1] - 1 },
		//south-southeast
		{ my_pos[0] + 1, my_pos[1] - 2 },
		//south-southwest
		{ my_pos[0] - 1, my_pos[1] - 2 },
		// southwest
		{ my_pos[0] - 2, my_pos[1] - 1 }
	};

	// check the squares
	for (int i = 0; i < 8; i++)
	{
		position pos = to_check[i];
		
		// is this position on the board?
		if (board.withinBounds(pos))
		{
			// get the piece at the square in question (if any)
			Piece* target = board.getPieceAt(pos);

			// is the square unoccupied?
			if (target == nullptr)
			{
				move m;
				m.piece = this;
				m.pos_from = my_pos;
				m.pos_to = pos;

				moves.push_back(m);
			}
			// is the square occupied by an enemy piece?
			else if (target->getColor() != color)
			{
				move m;
				m.piece = this;
				m.pos_from = my_pos;
				m.pos_to = pos;
				m.capture = true;
				m.captured = target;

				moves.push_back(m);
			}

		}
	}

	return moves;
}
