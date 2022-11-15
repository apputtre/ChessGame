#pragma once

#include "Piece.h"

class Pawn : public Piece {

public:
	Pawn(PieceType type, std::initializer_list<int> pos, PlayerColor color);
	vector<position> getMoves(vector<Piece*> &gameboard) override;
};
