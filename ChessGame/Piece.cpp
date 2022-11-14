#include "Piece.h"

Piece::Piece(PieceType type, std::initializer_list<int> pos, bool is_white)
{
	this->type = type;
	this->pos = { *pos.begin(), *(pos.begin() + 1) };
	this->is_white = is_white;
}

position Piece::getPos()
{
	return pos;
}

void Piece::setPos(std::initializer_list<int> pos)
{
	this->pos = { *pos.begin(), *(pos.begin() + 1) };
	has_moved = true;
}

bool Piece::isWhite()
{
	return is_white;
}

bool Piece::hasMoved()
{
	return has_moved;
}

PieceType Piece::getType()
{
	return type;
}

 vector<position> Piece::getMoves(vector<Piece> &gameboard)
{
	vector<position> moves;

	return moves;
}

 Piece* Piece::pieceAt(vector<Piece> &gameboard, std::initializer_list<int> pos)
 {
	 position to_find = { *pos.begin(), *(pos.begin() + 1) };

	 for (vector<Piece>::iterator it = gameboard.begin(); it < gameboard.end(); it++)
	 {
		 if ((*it).getPos() == to_find)
		 {
			 return &(*it);
		 }
	 }

	 return nullptr;
 }

