#include "Pawn.h"

Pawn::Pawn(PlayerColor color) : Piece(PAWN, color) {}

vector<move> Pawn::getMoves(Chessboard& board)
{

	vector<move> moves;

	int forward_dir = ((color == WHITE) ? 1 : -1);

	// get our position
	position my_pos = board.getPosOf(this);

	// can we move at all (are we not against the top edge of the board?)
	if (my_pos[1] < 7)
	{
		// can we move straight ahead?
		Piece* target = board.getPieceAt({ my_pos[0], my_pos[1] + forward_dir });

		if (target == nullptr)
		{
			// tile ahead is unoccupied
			move m;
			m.piece = this;
			m.pos_from = my_pos;
			m.pos_to = { my_pos[0], my_pos[1] + forward_dir };

			moves.push_back(m);

			// can we double move?
			if (my_pos[1] < 6)
			{
				if (board.getPieceAt({my_pos[0], my_pos[1] + 2 * forward_dir}) == nullptr && !has_moved)
				{
					move m;
					m.piece = this;
					m.pos_from = my_pos;
					m.pos_to = { my_pos[0], my_pos[1] + 2 * forward_dir };

					moves.push_back(m);
				}
			}
		}

		// can we move to a diagonal square?
		// checking northwest
		if (my_pos[0] > 0)
		{
			// en passant?
			if (target != nullptr && target->getColor() != color && !has_moved)
			{
				move m;
				m.piece = this;
				m.pos_from = my_pos;
				m.pos_to = { my_pos[0] - 1, my_pos[1] + forward_dir };
				m.capture = true;
				m.captured = target;

				moves.push_back(m);
			}

			// diagonal capture?
			Piece* nw_piece = board.getPieceAt({my_pos[0] - 1, my_pos[1] + forward_dir});
			if (nw_piece != nullptr && target->getColor() != color)
			{
				move m;
				m.piece = this;
				m.pos_from = my_pos;
				m.pos_to = { my_pos[0] - 1, my_pos[1] + forward_dir };
				m.capture = true;
				m.captured = nw_piece;

				moves.push_back(m);
			}

		}

		// checking northeast
		if (my_pos[0] < 7)
		{
			// en passant?

			if (target != nullptr && target->getColor() != color && !has_moved)
			{
				move m;
				m.piece = this;
				m.pos_from = my_pos;
				m.pos_to = { my_pos[0] + 1, my_pos[1] + forward_dir };
				m.capture = true;
				m.captured = target;

				moves.push_back(m);
			}

			// diagonal capture
			Piece* ne_piece = board.getPieceAt({ my_pos[0] + 1, my_pos[1] + forward_dir });
			if (ne_piece != nullptr && ne_piece->getColor() != color)
			{
				move m;
				m.piece = this;
				m.pos_from = my_pos;
				m.pos_to = { my_pos[0] + 1, my_pos[1] + forward_dir };
				m.capture = true;
				m.captured = ne_piece;

				moves.push_back(m);
			}
		}

	}

	return moves;
}
