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

bool Piece::check_castle(Chessboard& board, Piece* rook, Piece* king)
{
	// are these pieces of the appropriate types?
	if (rook->getType() == ROOK && king->getType() == KING)
	{
		// do these pieces belong to the same player?
		if (rook->getColor() == king->getColor())
		{
			// have either of these pieces moved?
			if (!rook->has_moved && !king->has_moved)
			{
				position king_pos = board.getPosOf(king);
				position rook_pos = board.getPosOf(rook);

				// is the king in check?
				PlayerColor enemy_color;
				if (rook->getColor() == WHITE)
					enemy_color = BLACK;
				else
					enemy_color = WHITE;
				
				if (!is_square_threatened(board, king_pos, enemy_color))
				{
					position dir = (rook_pos - king_pos).normalize();

					// can the rook move the the square next to the king?
					if (rook->isLegalMove(king_pos + dir, board))
					{
						// are either of the two squares next to the king threatened?
						if (!is_square_threatened(board, king_pos + dir, enemy_color) && !is_square_threatened(board, king_pos + dir + dir, enemy_color))
						{
							return true;
						}
					}
				}
			}
		}
	}
}

bool Piece::is_square_obstructed(Chessboard& board, position pos)
{
	Piece* piece_at_pos = board.getPieceAt(pos);

	if (piece_at_pos != nullptr)
		return (piece_at_pos->getColor() == getColor());

	return false;
}

bool Piece::is_square_threatened(Chessboard& board, position pos, PlayerColor color)
{
	// get a list of pieces which could threaten the square
	vector<Piece*> pieces = Piece::getPieces(board, color);
	vector<move> moves;

	for (auto it = pieces.begin(); it < pieces.end(); it++)
	{
		vector<move> m;
		m = (*it)->getMoves(board);

		moves.insert(moves.end(), m.begin(), m.end());
	}

	for (auto it = moves.begin(); it < moves.end(); it++)
		if ((*it).pos_to == pos)
			return true;

	return false;
}

bool Piece::kingInCheck(Chessboard& board, PlayerColor color)
{
	// get the king
	Piece* king = nullptr;
	std::vector<Piece*> pieces = getPieces(board, color);

	for (auto it = pieces.begin(); it < pieces.end(); it++)
	{
		if ((*it)->getType() == KING)
		{
			king = (*it);
		}
	}

	if (king == nullptr)
	{
		throw (std::invalid_argument("There is no king on the board!"));
	}

	PlayerColor enemy_color = (color == WHITE ? BLACK : WHITE);

	return is_square_threatened(board, board.getPosOf(king), enemy_color);

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

PlayerColor Piece::getColor() const
{
	return color;
}


PieceType Piece::getType() const
{
	return type;
}

char Piece::getErrorFlags() const
{
	return error_flags;
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

 std::vector<move> Piece::getMoves(Chessboard& board)
 {
	 std::vector<move> moves;

	 for (int row = 0; row < 8; row++)
		 for (int col = 0; col < 8; col++)
			 if (this->isLegalMove(position{ col, row }, board))
				 moves.push_back(this->getMove(position{ col, row }, board));

	 return moves;
 }

 std::vector<Piece*> Piece::getPieces(Chessboard& board, PlayerColor color)
 {
	 std::vector<Piece*> piece_vec = board.getPieces();
	 std::vector<Piece*> new_piece_vec;

	 for (auto it = piece_vec.begin(); it < piece_vec.end(); it++)
		 if ((*it)->getColor() == color)
			 new_piece_vec.push_back(*it);

	return new_piece_vec;
}

 ostream& operator<<(ostream& os, const Piece& rval)
 {
	 string to_print;

	 to_print += "[";

	 rval.getColor() == WHITE ? to_print += "white " : to_print += "black ";

	 if (rval.getType() == PAWN)
		 to_print += "pawn";
	 else if (rval.getType() == KNIGHT)
		 to_print += "knight";
	 else if (rval.getType() == BISHOP)
		 to_print += "bishop";
	 else if (rval.getType() == ROOK)
		 to_print += "rook";
	 else if (rval.getType() == KING)
		 to_print += "king";
	 else if (rval.getType() == QUEEN)
		 to_print += "queen";

	 to_print += "]";

	 cout << to_print;

	 return os;

 }
