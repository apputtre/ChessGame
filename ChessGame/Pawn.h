#pragma once

#include "chessdefs.h"
#include "Piece.h"

using namespace chess;

class Pawn : public Piece {

public:
	Pawn(PlayerColor color);
	vector<move> getMoves(Chessboard& board) override;
};
