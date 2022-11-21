#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include "chessdefs.h"
#include "Chessboard.h"

using std::string;
using std::cout;
using std::cin;
using std::vector;

using namespace chess;

class Piece
{
protected:
	PlayerColor color;
	PieceType type;

	vector<move> crawl(Chessboard& board, position dir);
	vector<move> check_diagonals(Chessboard& board);
	vector<move> check_cardinals(Chessboard& board);

public:
	bool has_moved = false;

	Piece(PieceType type, PlayerColor = WHITE);
	Piece(PlayerColor color = WHITE);

	PlayerColor getColor();
	PieceType getType();

	virtual vector<move> getMoves(Chessboard& board);
};
