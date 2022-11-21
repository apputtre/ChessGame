#pragma once

#include <array>
#include <iostream>

// forward declare Piece
class Piece;

namespace chess
{
	typedef std::array<int, 2> position;

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


	struct move {
		// the piece that moved
		Piece* piece = nullptr;
		// where the piece moved from
		position pos_from;
		// where the piece moved to
		position pos_to;
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
	};

}

