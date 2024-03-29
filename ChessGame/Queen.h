#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(PlayerColor color);

	vector<move> getMoves(Chessboard& board) override;
	bool isLegalMove(position pos, Chessboard& board) override;
};
