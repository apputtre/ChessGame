#pragma once

#include "Piece.h"

class Pawn : public Piece {

public:
	Pawn(PlayerColor color);
	vector<move> getMoves(chessboard& board) override;
};
