#include "Piece.h"

vector<move> Piece::crawl(Chessboard& board, position dir)
{
	vector<move> moves;

	position my_pos = board.getPosOf(this);

	position check_pos = {my_pos[0] + dir[0], my_pos[1] + dir[1]};

	if (!board.withinBounds(check_pos))
		return moves;

	while (board.withinBounds(check_pos))
	{
		Piece* target = board.getPieceAt(check_pos);

		if (target == nullptr)
		{
			move m;
			m.piece = this;
			m.pos_from = my_pos;
			m.pos_to = check_pos;

			moves.push_back(m);
		}
		else if (target->getColor() != getColor())
		{
			move m;
			m.piece = this;
			m.pos_from = my_pos;
			m.pos_to = check_pos;
			m.capture = true;
			m.captured = target;

			moves.push_back(m);

			return moves;
		}

		check_pos[0] += dir[0];
		check_pos[1] += dir[1];
	}

	return moves;
}

vector<move> Piece::check_diagonals(Chessboard& board)
{
	vector<move> moves;

	position my_pos = board.getPosOf(this);

	vector<move> diagonal;

	// check northwest
	position dir = { -1, 1 };
	diagonal = crawl(board, dir);
	moves.insert(moves.begin(), diagonal.begin(), diagonal.end());
	
	// check northeast
	dir = { 1, 1 };
	diagonal = crawl(board, dir);
	moves.insert(moves.begin(), diagonal.begin(), diagonal.end());

	// check southeast
	dir = { 1, -1 };
	diagonal = crawl(board, dir);
	moves.insert(moves.begin(), diagonal.begin(), diagonal.end());

	// check southwest
	dir = { -1, -1 };
	diagonal = crawl(board, dir);
	moves.insert(moves.begin(), diagonal.begin(), diagonal.end());
	
	return moves;
}

vector<move> Piece::check_cardinals(Chessboard& board)
{
	vector<move> moves;
	position my_pos = board.getPosOf(this);
	vector<move> cardinal;

	// check north
	position dir = { 0, 1 };
	cardinal = crawl(board, dir);
	moves.insert(moves.end(), cardinal.begin(), cardinal.end());

	// check east
	dir = { 1, 0 };
	cardinal = crawl(board, dir);
	moves.insert(moves.end(), cardinal.begin(), cardinal.end());

	// check south
	dir = { 0, -1 };
	cardinal = crawl(board, dir);
	moves.insert(moves.end(), cardinal.begin(), cardinal.end());

	// check west
	dir = { -1, 0 };
	cardinal = crawl(board, dir);
	moves.insert(moves.end(), cardinal.begin(), cardinal.end());

	return moves;
}

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
