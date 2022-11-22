#include <iostream>
#include "Piece.h"
#include "Knight.h"
#include "Pawn.h"
#include <regex>
#include "Chessboard.h"
#include "chessdefs.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace chess;

Chessboard board;

void print_board(Chessboard& board);
int do_turn(string input);
void setup_board();

int main()
{
	setup_board();

	string player_input;

	bool exit = false;
	while (!exit)
	{
		print_board(board);

		cout << "\n\n";

		bool player_entered_turn = false;
		while (!player_entered_turn)
		{
			cout << "Player move: ";
			std::getline(cin, player_input);

			player_entered_turn = !do_turn(player_input);
		}

		cout << "\n";
	}

	return 0;
}

void print_board(Chessboard& board)
{
	Piece* piece_ptr;
	bool white_square = true;
	for (int row = 7; row >= 0; row--)
	{
		cout << (row + 1) << " ";
		for (int col = 0; col < 8; col++)
		{
			piece_ptr = board.getPieceAt({ col, row });
			if (piece_ptr == nullptr)
			{
				cout << (white_square ? "OO" : "##");
			}
			else
			{
				cout << (piece_ptr->getColor() == WHITE ? "w" : "b");

				switch (piece_ptr->getType())
				{
				case PAWN:
					cout << 'p';
					break;
				case KNIGHT:
					cout << 'k';
					break;
				case BISHOP:
					cout << 'b';
					break;
				case ROOK:
					cout << 'r';
					break;
				case QUEEN:
					cout << 'Q';
					break;
				case KING:
					cout << 'K';
					break;
				default:
					cout << "!";
					break;
				}
			}
			
			cout << " ";
			white_square = !white_square;
		}
		cout << "\n";
		if (row != 0)
			cout << "\n";
		white_square = !white_square;
	}
	cout << "  ";
	for(int i = 0; i < 8; cout << (char) ('a' + i++) << "  ") {}
}

int do_turn(string player_input)
{

	// matches 'letter digit space letter digit'
	// e.g. 'a1 a2'
	std::regex input_exp("([a-h])(\\d)\\s([a-h])(\\d)");
	std::smatch matches;

	if (!std::regex_match(player_input, matches, input_exp))
	{
		cout << "Invalid command\n";
		return 1;
	}

	// matches[0] contains the full input (for some reason)
	position src_pos = { matches[1].str()[0] - 'a', matches[2].str()[0] - '1'};
	position dest_pos = { matches[3].str()[0] - 'a', matches[4].str()[0] - '1' };

	Piece* piece_ptr = board.getPieceAt(src_pos);

	if (piece_ptr == nullptr)
	{
		cout << "There is no piece at the specified square\n";
		return 1;
	}

	/*
	switch (piece_ptr->getType())
	{
	case PAWN:
		piece_ptr = (Pawn*)piece_ptr;
		break;
	case KNIGHT:
		piece_ptr = (Knight*)piece_ptr;
		break;
	case BISHOP:
		piece_ptr = (Bishop*)piece_ptr;
		break;
	default:
		cout << "ERROR" << "\n";
		return 1;
	}
	*/

	// get the moves the piece can make
	vector<move> moves = piece_ptr->getMoves(board);

	// is this a legal move?
	// if so, fetch the move
	bool move_legal = false;
	move* m = nullptr;
	for (vector<move>::iterator it = moves.begin(); it < moves.end(); it++)
		if ((*it).pos_from == src_pos && (*it).pos_to == dest_pos)
		{
			move_legal = true;
			m = &(*it);
			break;
		}

	if (move_legal)
	{
		if (m->capture)
			board.takeOffBoard(m->captured);

		board.movePiece(piece_ptr, dest_pos);
		piece_ptr->has_moved = true;
	}
	else
	{
		cout << "Illegal move\n";
		return 1;
	}

	return 0;
}

void setup_board()
{
	// set up white's back row
	board.putOnBoard(new Rook(WHITE), { 0, 0 });
	board.putOnBoard(new Knight(WHITE), { 1, 0 });
	board.putOnBoard(new Bishop(WHITE), { 2, 0 });
	board.putOnBoard(new Queen(WHITE), { 3, 0 });
	board.putOnBoard(new King(WHITE), { 4, 0 });
	board.putOnBoard(new Bishop(WHITE), { 5, 0 });
	board.putOnBoard(new Knight(WHITE), { 6, 0 });
	board.putOnBoard(new Rook(WHITE), { 7, 0 });
	// white pawns
	for (int i = 0; i < 8; board.putOnBoard(new Pawn(WHITE), { i++, 1 })) {}

	// set up black's back row
	board.putOnBoard(new Rook(BLACK), { 0, 7 });
	board.putOnBoard(new Knight(BLACK), { 1, 7 });
	board.putOnBoard(new Bishop(BLACK), { 2, 7 });
	board.putOnBoard(new Queen(BLACK), { 3, 7 });
	board.putOnBoard(new King(BLACK), { 4, 7 });
	board.putOnBoard(new Bishop(BLACK), { 5, 7 });
	board.putOnBoard(new Knight(BLACK), { 6, 7 });
	board.putOnBoard(new Rook(BLACK), { 7, 7 });
	// black pawns
	for (int i = 0; i < 8; board.putOnBoard(new Pawn(BLACK), { i++, 6 })) {}
}
