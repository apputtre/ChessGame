#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::vector;

typedef std::array<int, 2> position;

enum PieceType
{
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
};

class Piece
{
protected:
	position pos;

	bool is_white;
	bool has_moved = false;
	PieceType type;

public:
	Piece(PieceType type, std::initializer_list<int> pos, bool is_white = true);

	position getPos();
	void setPos(std::initializer_list<int> pos);

	bool isWhite();
	bool hasMoved();
	PieceType getType();

	virtual vector<position> getMoves(vector<Piece> &gameboard);

	static Piece* pieceAt(vector<Piece> &gameboard, std::initializer_list<int> pos);
};
