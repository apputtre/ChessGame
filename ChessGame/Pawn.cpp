#include "Pawn.h"

Pawn::Pawn(std::initializer_list<int> pos, bool is_white) : Piece(pos, is_white) {}

vector<position> Pawn::getMoves(vector<Piece> gameboard)
{
	vector<position> moves;

	// generate initial list of moves

	position p = {col, row + 1};
	moves.push_back(p);

	return moves;
}
