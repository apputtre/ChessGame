#include "Piece.h"

Piece::Piece(std::initializer_list<int> pos, bool is_white)
{
	col = *pos.begin();
	row = *(pos.begin() + 1);
	this->is_white = is_white;
}

int Piece::getRow()
{
	return row;
}

int Piece::getCol()
{
	return col;
}

void Piece::setPos(std::initializer_list<int> params)
{
	col = *params.begin();
	row = *(params.begin() + 1);
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

 vector<position> Piece::getMoves(vector<Piece> gameboard)
{
	vector<position> moves;

	return moves;
}

 Piece Piece::pieceAt(vector<Piece> gameboard, position pos)
 {
	 // vector<Piece>::iterator it;
	 // it = std::search(gameboard.begin(), gameboard.end(), &pos);
	 // return *it;
	 Piece p({ 0, 0 });
	 return p;
 }
