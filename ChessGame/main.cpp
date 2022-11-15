#include <iostream>
#include "Piece.h"
#include "Pawn.h"
#include <regex>

void print_board(vector<Piece*>& gameboard);
int do_turn(string input);


vector<Piece*> gameboard;

int main()
{
	string player_input;

	Pawn* p = new Pawn(PAWN, { 1, 0 }, true);

	gameboard.push_back(p);

	bool exit = false;
	while (!exit)
	{
		print_board(gameboard);

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

void print_board(vector<Piece*>& gameboard)
{
	Piece* p;
	bool white_square = true;
	for (int row = 7; row >= 0; row--)
	{
		cout << (row + 1) << " ";
		for (int col = 0; col < 8; col++)
		{
			p = Piece::pieceAt(gameboard, { col, row });
			if (p == nullptr)
			{
				cout << (white_square ? "OO" : "##");
			}
			else
			{
				cout << (p->isWhite() ? "w" : "b");

				switch (p->getType())
				{
				case PAWN:
					cout << 'p';
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

	Piece* piece_ptr = Piece::pieceAt(gameboard, src_pos);

	if (piece_ptr == nullptr)
	{
		cout << "There is no piece at the specified square\n";
		return 1;
	}

	switch (piece_ptr->getType())
	{
	case PAWN:
		piece_ptr = (Pawn*)piece_ptr;
		break;
	default:
		cout << "ERROR" << "\n";
		return 1;
	}

	// is this a legal move?
	
	// get the moves the pieces can make
	vector<position> moves = piece_ptr->getMoves(gameboard);

	if (std::find(moves.begin(), moves.end(), dest_pos) == moves.end())
	{
		cout << "Illegal move\n";
		return 1;
	}

	
	// is this a capture?
	Piece* piece_at_dest = Piece::pieceAt(gameboard, dest_pos);
	if (piece_at_dest != nullptr)
	{
		// if so, remove the piece
		// remove / erase idiom
		gameboard.erase(std::remove(gameboard.begin(), gameboard.end(), piece_at_dest), gameboard.end());
		delete piece_at_dest;
		cout << "Capture!\n";
	}

	piece_ptr->setPos(dest_pos);

	return 0;
}