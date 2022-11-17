#pragma once

#include <array>
#include <iostream>

// forward declare Piece
class Piece;

namespace chess
{
	
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

	typedef std::array<int, 2> position;

	struct move {
		// the piece that moved
		Piece* piece;
		// where the piece moved from
		position pos_from;
		// where the piece moved to
		position pos_to;
		// was this a capture?
		bool capture;
		// the piece that was captured (if any)
		Piece* captured;
		// was this a castle? (we can infer whether it was kingside or queenside from pos_to)
		bool castle;
		// was this a promotion?
		bool promotion;
		// what the piece was promoted from
		PieceType promo_from;
		// what the piece was promoted to
		PieceType promo_to;
	};

}

