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

enum PlayerColor
{
	BLACK,
	WHITE
};

class Piece
{
protected:
	position pos;

	PlayerColor color;
	bool has_moved = false;
	PieceType type;

public:
	Piece(PieceType type, std::initializer_list<int> pos, PlayerColor color = WHITE);

	position getPos();
	void setPos(position pos);

	PlayerColor getColor();
	bool hasMoved();
	PieceType getType();

	virtual vector<position> getMoves(vector<Piece*> &gameboard);

	static Piece* pieceAt(vector<Piece*> &gameboard, position pos);
};
