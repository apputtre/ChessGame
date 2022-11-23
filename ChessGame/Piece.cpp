#include "Piece.h"

vector<move> Piece::crawl(Chessboard& board, position dir, int distance)
{
	vector<move> moves;

	// get our position
	position my_pos = board.getPosOf(this);

	position check_pos = my_pos + dir;

	for(int i = distance; i > 0 && isLegalMove(check_pos, board); i--)
	{
		move m = getMove(check_pos, board);
		moves.push_back(m);

		if (m.capture)
			return moves;

		check_pos += dir;
	}

	return moves;
}

vector<move> Piece::check_diagonals(Chessboard& board)
{
	vector<move> moves;
	position my_pos = board.getPosOf(this);
	vector<move> diagonal;

	// check northwest
	diagonal = crawl(board, Northwest);
	moves.insert(moves.begin(), diagonal.begin(), diagonal.end());
	
	// check northeast
	diagonal = crawl(board, Northeast);
	moves.insert(moves.begin(), diagonal.begin(), diagonal.end());

	// check southeast
	diagonal = crawl(board, Southeast);
	moves.insert(moves.begin(), diagonal.begin(), diagonal.end());

	// check southwest
	diagonal = crawl(board, Southwest);
	moves.insert(moves.begin(), diagonal.begin(), diagonal.end());
	
	return moves;
}

vector<move> Piece::check_cardinals(Chessboard& board)
{
	vector<move> moves;
	position my_pos = board.getPosOf(this);
	vector<move> cardinal;

	// check north
	cardinal = crawl(board, North);
	moves.insert(moves.end(), cardinal.begin(), cardinal.end());

	// check east
	cardinal = crawl(board, East);
	moves.insert(moves.end(), cardinal.begin(), cardinal.end());

	// check south
	cardinal = crawl(board, South);
	moves.insert(moves.end(), cardinal.begin(), cardinal.end());

	// check west
	cardinal = crawl(board, West);
	moves.insert(moves.end(), cardinal.begin(), cardinal.end());

	return moves;
}

bool Piece::is_square_obstructed(Chessboard& board, position pos)
{
	Piece* piece_at_pos = board.getPieceAt(pos);

	if (piece_at_pos != nullptr)
		return (piece_at_pos->getColor() == getColor());

	return false;
}

Piece::Piece(PieceType type, PlayerColor color)
{
	error_flags = 0;
	this->type = type;
	this->color = color;
}

Piece::Piece(PlayerColor color)
{
	error_flags = 0;
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

char Piece::getErrorFlags()
{
	return error_flags;
}

 vector<move> Piece::getMoves(Chessboard& board)
{
	vector<move> moves;

	return moves;
}

 bool Piece::isLegalMove(position pos_to, Chessboard& board)
 {
	error_flags = 0;

	// is this move on the board?
	if (!board.withinBounds(pos_to))
	{
		error_flags |= NOT_ON_BOARD;
		return false;
	}

	// is the destination square obstructed by a friendly piece?
	if (is_square_obstructed(board, pos_to))
	{
		error_flags |= OBSTRUCTED_SQUARE;
		return false;
	}

	 return true;
 }

 move Piece::getMove(position pos_to, Chessboard& board)
 {
	 if (!isLegalMove(pos_to, board))
		 throw(std::invalid_argument("getMove was given illegal position"));

	 // get our position
	 position my_pos = board.getPosOf(this);
	 // get the piece at the destination square
	 Piece* to_piece = board.getPieceAt(pos_to);

	// was this a simple move (no capture?)
	 if (to_piece == nullptr)
		 return move(this, my_pos, pos_to);
	 else
		 // this was a capture
		 return move(this, my_pos, pos_to, to_piece);
 }
