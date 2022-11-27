#pragma once

#include "Piece.h"

class King : public Piece
{
public:
	King(PlayerColor color);

	vector<move> getMoves(Chessboard& board) override;
	bool isLegalMove(position to_pos, Chessboard& board) override;
};
