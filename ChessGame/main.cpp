#include <iostream>
#include "Piece.h"
#include "Pawn.h"

void print_board(vector<Piece>& gameboard);

int main()
{
	vector<Piece> gameboard;
	Pawn p(PAWN, { 1, 0 }, true);
	gameboard.push_back(p);

	print_board(gameboard);

	return 0;
}

void print_board(vector<Piece>& gameboard)
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