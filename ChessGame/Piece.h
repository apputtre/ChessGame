#pragma once

#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::vector;

class Piece
{
	int position[2];
	string name;
	bool color, has_moved;

public:
	Piece();

	int* getPos();
	string getName();
	bool getColor();
	bool hasMoved();
	vector<int[2]> getMoves();
};
