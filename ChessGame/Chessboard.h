#pragma once

#include <array>
#include <vector>
#include "chessdefs.h"

using namespace chess;

class Chessboard
{
	// a 2d array to represent the positions of all the pieces
	std::array<std::array<Piece*, 8>, 8> pieces;

	// does this piece exist on or off the board?
	bool pieceExtant(const Piece* piece);

public:
	// is the specified position within the bounds of the board?
	bool withinBounds(position pos);
	// return a 1d array of all of the pieces
	std::vector<Piece*> getPieces();
	// given an already-created piece, put it on the board
	void putOnBoard(Piece* piece, position at_pos);
	// get the position of the specified piece on the board
	position getPosOf(const Piece* to_find);
	// get the piece on the board at the specified position
	Piece* getPieceAt(position pos);
	// is there a piece on the board at position pos?
	bool isPieceAt(position pos);
	// remove a piece from the board
	void takeOffBoard(Piece* piece);
	// move a piece to a new location
	// if a piece exists at the destination, remove it
	void movePiece(Piece* to_move, position pos_to);

	Chessboard();
	~Chessboard();
};
