#pragma once

#include "Piece.h"

using namespace chess;

class Bishop : public Piece
{
public:
	Bishop(PlayerColor color);

	vector<move> getMoves(Chessboard& board) override;
	bool isLegalMove(position pos, Chessboard& board) override;
};
