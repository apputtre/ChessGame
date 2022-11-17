#include "Piece.h"

Piece::Piece(PieceType type, PlayerColor color)
{
	this->type = type;
	this->color = color;
}

Piece::Piece(PlayerColor color)
{
	this->type = DEFAULT;
	this->color = color;
}

PlayerColor Piece::getColor()
{
	return color;
}


PieceType Piece::getType()
{
	return type;
}

 vector<move> Piece::getMoves(Chessboard& board)
{
	vector<move> moves;

	cout << "This should never be printed!\n";

	return moves;
}
