#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <array>

using std::string;
using std::cout;
using std::cin;
using std::vector;

typedef std::array<int, 2> position;

class Piece
{
protected:
	int row, col;

	bool is_white;
	bool has_moved = false;

public:
	Piece(std::initializer_list<int> pos, bool is_white = true);

	int getRow();
	int getCol();
	void setPos(std::initializer_list<int> params);

	bool isWhite();
	bool hasMoved();

	virtual vector<position> getMoves(vector<Piece> gameboard);
};
