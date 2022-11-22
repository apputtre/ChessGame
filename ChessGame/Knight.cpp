#include "Knight.h"

Knight::Knight(PlayerColor color) : Piece(KNIGHT, color) {}

vector<move> Knight::getMoves(Chessboard& board)
{
	vector<move> moves;

	position my_pos = board.getPosOf(this);

	// squares to check
	position to_check[8] = {
		//northwest
		{my_pos[0] - 2, my_pos[1] + 1 },
		//north-northwest
		{ my_pos[0] - 1, my_pos[1] + 2 },
		//north-northeast
		{ my_pos[0] + 1, my_pos[1] + 2 },
		//northeast
		{ my_pos[0] + 2, my_pos[1] + 1 },
		//southeast
		{ my_pos[0] + 2, my_pos[1] - 1 },
		//south-southeast
		{ my_pos[0] + 1, my_pos[1] - 2 },
		//south-southwest
		{ my_pos[0] - 1, my_pos[1] - 2 },
		// southwest
		{ my_pos[0] - 2, my_pos[1] - 1 }
	};

	// check the squares
	for (int i = 0; i < 8; i++)
		if (isLegalMove(to_check[i], board))
			moves.push_back(getMove(to_check[i], board));

	return moves;
}

bool Knight::isLegalMove(position pos_to, Chessboard& board)
{
	// check if the square is obstructed or off the board
	if (!Piece::isLegalMove(pos_to, board))
		return false;

	// get our position
	position my_pos = board.getPosOf(this);
	// get difference in my_pos and pos_to
	position diff = my_pos - pos_to;

	if (abs(diff[0]) == 2 && abs(diff[1]) == 1 || abs(diff[0]) == 1 && abs(diff[1] == 2))
		return true; 
}
