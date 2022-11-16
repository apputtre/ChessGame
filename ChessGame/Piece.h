#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include "chessdefs.h"

using std::string;
using std::cout;
using std::cin;
using std::vector;

using namespace chess;

class Piece
{
protected:
	PlayerColor color;
	bool has_moved = false;
	PieceType type;

public:
	Piece(PieceType type, PlayerColor = WHITE);
	Piece(PlayerColor color = WHITE);

	PlayerColor getColor();
	bool hasMoved();
	PieceType getType();

	virtual vector<move> getMoves(chessboard& board);
};
