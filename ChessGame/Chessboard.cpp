#include "Chessboard.h"
#include <exception>

// constructors
Chessboard::Chessboard()
{
}

Chessboard::~Chessboard()
{
}

// private
bool Chessboard::pieceExtant(const Piece* piece)
{
	std::vector<Piece*> piece_vec = getPieces();

	bool found_piece = std::find(piece_vec.begin(), piece_vec.end(), piece) != piece_vec.end();

	return found_piece;
}

// public
bool Chessboard::withinBounds(position pos)
{
	return (pos[0] >= 0 && pos[0] <= 7 && pos[1] >= 0 && pos[1] <= 7);
}

std::vector<Piece*> Chessboard::getPieces()
{
	std::vector<Piece*> piece_vec;

	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
			if (pieces[row][col] != nullptr)
				piece_vec.push_back(pieces[row][col]);

	return piece_vec;
}

void Chessboard::putOnBoard(Piece* piece, position at_pos)
{
	if (!pieceExtant(piece))
	{
		if (getPieceAt(at_pos) == nullptr)
		{
			pieces[at_pos[0]][at_pos[1]] = piece;
		}
		else
		{
			throw std::invalid_argument("position is already occupied");
		}
	}
	else
	{
		throw std::invalid_argument("piece already exists on board");
	}
}

position Chessboard::getPosOf(const Piece* to_find)
{
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
			if (pieces[row][col] == to_find)
				return { row, col };

	throw std::invalid_argument("piece does not exist");
}

Piece* Chessboard::getPieceAt(position pos)
{
	if (!withinBounds(pos))
		throw std::invalid_argument("position out of bounds");

	return pieces[pos[0]][pos[1]];
}

bool Chessboard::isPieceAt(position pos)
{
	if (!withinBounds(pos))
		throw std::invalid_argument("position out of bounds");

	return pieces[pos[0]][pos[1]] != nullptr;
}

void Chessboard::takeOffBoard(Piece* piece)
{
	if (pieceExtant(piece))
	{
		position pos = getPosOf(piece);

		pieces[pos[0]][pos[1]] = nullptr;
		delete piece;
	}
	else
	{
		throw std::invalid_argument("piece does not exist");
	}
}

void Chessboard::movePiece(Piece* to_move, position pos_to)
{
	if (!pieceExtant(to_move))
		throw std::invalid_argument("piece does not exist");

	if (getPieceAt(pos_to) != nullptr)
		takeOffBoard(getPieceAt(pos_to));

	position pos_from = getPosOf(to_move);

	pieces[pos_from[0]][pos_from[1]] = nullptr;
	pieces[pos_to[0]][pos_to[1]] = to_move;
}
