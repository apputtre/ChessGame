#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(PlayerColor color);

	vector<move> getMoves(Chessboard& board) override;
	bool isLegalMove(position to_pos, Chessboard& board) override;
};
