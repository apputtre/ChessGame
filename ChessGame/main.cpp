#include <iostream>
#include "Piece.h"
#include "Knight.h"
#include "Pawn.h"
#include <regex>
#include <algorithm>
#include "Chessboard.h"
#include "chessdefs.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

using namespace chess;

using std::cin;
using std::cout;

Chessboard board;

void print_board(Chessboard& board, Piece* show_moves_for = nullptr);
int do_turn(string input);
void setup_board();
move get_cpu_move(Chessboard& board, PlayerColor cpu_player);

int main()
{

	PlayerColor turn = WHITE;
	PlayerColor cpu_player = NULL_PLAYER;

	setup_board();

	string player_input;

	do
	{
		cout << "Which side would you like to play? (b/w): ";
		getline(cin, player_input);
		std::transform(player_input.begin(), player_input.end(), player_input.begin(), tolower);
		if (player_input == "b" || player_input == "black")
		{
			cpu_player = WHITE;
		}
		else if (player_input == "w" || player_input == "white")
		{
			cpu_player = BLACK;
		}
		else
		{
			cout << "please enter w/h.\n";
		}

	} while (cpu_player == NULL_PLAYER);
	cout << "\n";


	bool exit = false;
	while (!exit)
	{
		if (turn == cpu_player)
		{
			move cpu_move = get_cpu_move(board, cpu_player);

			if (cpu_move.capture)
				board.takeOffBoard(cpu_move.captured);

			board.movePiece(cpu_move.piece, cpu_move.pos_to);
			cpu_move.piece->has_moved = true;

			turn = (turn == WHITE ? BLACK : WHITE);
			continue;
		}


		print_board(board);
		cout << "\n\n";

		bool player_entered_turn = false;
		while (!player_entered_turn)
		{
			cout << "Player move: ";
			std::getline(cin, player_input);

			player_entered_turn = !do_turn(player_input);

		}

		turn = (turn == WHITE ? BLACK : WHITE);

		cout << "\n";
	}

	return 0;
}

void print_board(Chessboard& board, Piece* show_moves_for)
{
	std::vector<position> to_highlight;

	if (show_moves_for != nullptr)
	{
		std::vector<move> moves = show_moves_for->getMoves(board);

		for (auto it = moves.begin(); it < moves.end(); it++)
			to_highlight.push_back((*it).pos_to);

		cout << to_highlight.size() << "\n";
	}
	
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
				if (std::find(to_highlight.begin(), to_highlight.end(), position { col, row }) != to_highlight.end())
					cout << "XX";
				else
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
	std::regex input_exp_move("([a-h])(\\d)\\s([a-h])(\\d)");
	// matches !{command} space letter digit
	// e.g. !showmoves b3
	std::regex input_exp_debug("!(.*)\\s([a-h])(\\d)");
	std::smatch matches;

	if (std::regex_match(player_input, matches, input_exp_move))
	{
		position src_pos = { matches[1].str()[0] - 'a', matches[2].str()[0] - '1'};
		position dest_pos = { matches[3].str()[0] - 'a', matches[4].str()[0] - '1' };

		Piece* piece_ptr = board.getPieceAt(src_pos);

		if (piece_ptr == nullptr)
		{
			cout << "There is no piece at the specified square.\n";
			return 1;
		}

		// is this a legal move?
		if (piece_ptr->isLegalMove(dest_pos, board))
		{
			// get the move
			move m = piece_ptr->getMove(dest_pos, board);

			if (m.capture)
				board.takeOffBoard(m.captured);

			board.movePiece(piece_ptr, dest_pos);
			piece_ptr->has_moved = true;
		}
		else
		{
			int flags = piece_ptr->getErrorFlags();

			if ((flags & ILLEGAL_SQUARE) > 0)
			{
				cout << "The piece cannot move to that square.\n";
			}

			if ((flags & NOT_FIRST_TURN) > 0)
			{
				cout << "The piece can only move that way on its first turn.\n";
			}

			if ((flags & OBSTRUCTED_SQUARE) > 0)
			{
				cout << "The destination square is obstructed by a piece that can't be captured.\n";
			}

			if ((flags & OBSTRUCTED_PATH) > 0)
			{
				cout << "The piece is blocked by another in it's path.\n";
			}

			if ((flags & KING_IN_CHECK) > 0)
			{
				cout << "Your move must get your king out of check.\n";
			}

			if ((flags & NOT_ON_BOARD) > 0)
			{
				cout << "The square you selected is not on the board (how did you even select it?)\n";
			}

			return 1;
		}
	}
	else if (std::regex_match(player_input, matches, input_exp_debug))
	{
		string command = matches[1].str();
		position pos = position{ matches[2].str()[0] - 'a', matches[3].str()[0] - '1' };

		if (command == "sm")
		{
			if (board.getPieceAt(pos) != nullptr)
			{
				print_board(board, board.getPieceAt(pos));
				cout << "\n";
			}
		}
		else if (command == "del")
		{
			if (board.getPieceAt(pos) != nullptr)
			{
				board.takeOffBoard(board.getPieceAt(pos));
				return 0;
			}
		}
		else
		{
			cout << "Command \'" << command << "\' not recognized\n";
		}

		return 1;
	}
	else
	{
		cout << "Invalid input\n";
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

move get_cpu_move(Chessboard& board, PlayerColor cpu_player)
{
	std::vector<move> available_moves;
	std::vector<Piece*> my_pieces = Piece::getPieces(board, cpu_player);
	for (auto iter_piece = my_pieces.begin(); iter_piece < my_pieces.end(); iter_piece++)
	{
		std::vector<move> to_insert = (*iter_piece)->getMoves(board);
		available_moves.insert(available_moves.begin(), to_insert.begin(), to_insert.end());
	}
	srand(time(NULL));
	int r = rand() % available_moves.size();
	return available_moves[r];
}
