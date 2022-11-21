#pragma once

#include "Piece.h"

class Queen : public Piece
{
	Queen(PlayerColor color);

	vector<move> getMoves(Chessboard& board) override;
};
