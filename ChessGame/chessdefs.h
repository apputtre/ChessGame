#pragma once

#include <array>
#include <iostream>
#include <exception>

class Piece;

namespace chess
{
	struct position
	{
		int col_num, row_num;

		position normalize()
		{
			if (col_num < 0)
				col_num = -1;
			else if (col_num > 0)
				col_num = 1;
			else
				col_num = 0;

			if (row_num < 0)
				row_num = -1;
			else if (row_num > 0)
				row_num = 1;
			else
				row_num = 0;

			return *this;
		}

		void operator=(const position& rval)
		{
			this->col_num = rval.col_num;
			this->row_num = rval.row_num;
		}

		bool operator==(const position& rval)
		{
			return this->col_num == rval.col_num && this->row_num == rval.row_num;
		}

		bool operator!=(const position& rval)
		{
			return !(*this == rval);
		}

		position operator+(const position& rval)
		{
			return { this->col_num + rval.col_num, this->row_num + rval.row_num };
		}

		void operator+=(const position& rval)
		{
			this->col_num += rval.col_num;
			this->row_num += rval.row_num;
		}

		position operator-(const position& rval)
		{
			return { this->col_num - rval.col_num, this->row_num - rval.row_num };
		}

		void operator-=(const position& rval)
		{
			this->col_num -= rval.col_num;
			this->row_num -= rval.row_num;
		}

		int operator[](const int& index)
		{
			if (index == 0)
				return col_num;
			else if (index == 1)
				return row_num;
			else
				throw(std::invalid_argument("index to position out of range"));
		}

	};

	const position North{ 0, 1 };
	const position Northeast{ 1, 1 };
	const position East{ 1, 0 };
	const position Southeast{ 1, -1 };
	const position South{ 0, -1 };
	const position Southwest{ -1, -1 };
	const position West{ -1, 0 };
	const position Northwest{ -1, 1 };

	const position Directions[8]{
		North,
		Northeast,
		East,
		Southeast,
		South,
		Southwest,
		West,
		Northwest
	};

	enum PieceType {
		DEFAULT,
		PAWN,
		KNIGHT,
		BISHOP,
		ROOK,
		QUEEN,
		KING
	};

	enum PlayerColor {
		WHITE,
		BLACK
	};

	enum IllegalMoveFlag {
		ILLEGAL_SQUARE =	0b00000001,			// the user has tried to move to a square which the piece can't move to
		NOT_FIRST_TURN =	0b00000010,			// the user has tried to perform an action which a piece can only do on its first move (double move, en passant, castling)	
		OBSTRUCTED_SQUARE = 0b00000100,			// the user has tried to move a piece to a square which is occupied by a friendly piece
		OBSTRUCTED_PATH =	0b00001000,			// the user has trued to move a piece to a square which is blocked by another piece
		KING_IN_CHECK =		0b00010000,			// the use has tried to make a move which does not take his king out of check
		NOT_ON_BOARD =		0b00100000,			// the user has tried to move a piece to a square which does not exist
	};

	struct move {
		// the piece that moved
		Piece* piece = nullptr;
		// where the piece moved from
		position pos_from = position{ -1, -1 };
		// where the piece moved to
		position pos_to = position{ -1, -1 };
		// was this a capture?
		bool capture = false;
		// the piece that was captured (if any)
		Piece* captured = nullptr;
		// was this a castle? (we can infer whether it was kingside or queenside from pos_to)
		bool castle = false;
		// was this a promotion?
		bool promotion = false;
		// what the piece was promoted from
		PieceType promo_from = DEFAULT;
		// what the piece was promoted to
		PieceType promo_to = DEFAULT;

		move() {}

		move(Piece* piece, position pos_from, position pos_to)
		{
			this->piece = piece;
			this->pos_from = pos_from;
			this->pos_to = pos_to;
		}

		move(Piece* piece, position pos_from, position pos_to, Piece* captured)
		{
			this->piece = piece;
			this->pos_from = pos_from;
			this->pos_to = pos_to;
			
			capture = true;
			this->captured = captured;
		}

		bool operator==(const move& rval)
		{
			return this->pos_to == rval.pos_to && this->pos_from == rval.pos_from;
		}
	};

}

