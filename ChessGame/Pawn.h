#pragma once

#include "chessdefs.h"
#include "Piece.h"
#include <math.h>

using namespace chess;

class Pawn : public Piece {

public:
	Pawn(PlayerColor color);
	vector<move> getMoves(Chessboard& board) override;
	bool isLegalMove(position pos_to, Chessboard& board) override;
};
