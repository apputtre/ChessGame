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

	vector<move> crawl(Chessboard& board, position dir, int distance = 8);
	vector<move> check_diagonals(Chessboard& board);
	vector<move> check_cardinals(Chessboard& board);
	bool is_square_obstructed(Chessboard& board, position pos);
	bool is_square_threatened(Chessboard& board, position pos, PlayerColor color);
	bool check_castle(Chessboard& board, Piece* rook, Piece* king);

	char error_flags;

public:
	bool has_moved = false;

	Piece(PieceType type, PlayerColor = WHITE);
	Piece(PlayerColor color = WHITE);

	PlayerColor getColor();
	PieceType getType();
	char getErrorFlags();
	std::vector<Piece*> getPieces(Chessboard& board, PlayerColor color);
	bool kingInCheck(Chessboard& board, PlayerColor color);

	virtual vector<move> getMoves(Chessboard& board);
	virtual bool isLegalMove(position pos_to, Chessboard& board);
	move getMove(position pos_to, Chessboard& board);
};
