#include "Piece.h"

Piece::Piece(PieceType type, std::initializer_list<int> pos, PlayerColor color)
{
	this->type = type;
	this->pos = { *pos.begin(), *(pos.begin() + 1) };
	this->color = color;
}

position Piece::getPos()
{
	return pos;
}

void Piece::setPos(position pos)
{
	this->pos = pos;
	has_moved = true;
}

PlayerColor Piece::getColor()
{
	return color;
}


bool Piece::hasMoved()
{
	return has_moved;
}

PieceType Piece::getType()
{
	return type;
}

 vector<position> Piece::getMoves(vector<Piece*> &gameboard)
{
	vector<position> moves;

	cout << "This should never be printed!\n";

	return moves;
}

 Piece* Piece::pieceAt(vector<Piece*> &gameboard, position pos)
 {
	 for (vector<Piece*>::iterator it = gameboard.begin(); it < gameboard.end(); it++)
	 {
		 if (gameboard[it - gameboard.begin()]->getPos() == pos)
		 {
			 return gameboard[it - gameboard.begin()];
		 }
	 }

	 return nullptr;
 }

