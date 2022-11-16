#pragma once

#include <array>
#include <iostream>

using std::cout;

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

	struct chessboard {
		std::array<std::array<Piece*, 8>, 8> pieces;
		
		position findPiece(Piece* to_find)
		{
			for (int row = 0; row < 8; row++)
				for (int col = 0; col < 8; col++)
					if (pieces[row][col] == to_find)
						return { row, col };
		}

		std::array<Piece*, 8>& operator[](int idx)
		{
			return pieces[idx];
		}
	};
	
	// encapsulates information about a move on the board
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

