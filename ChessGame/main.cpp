#include <iostream>
#include "Piece.h"
#include "Pawn.h"

int main()
{
	vector<Piece> gameboard;
	Pawn p({ 1, 0 }, true);
	gameboard.push_back(p);

	cout << p.getPos()[0] << ", " << p.getPos()[1] << "\n";
	cout << &gameboard << "\n";

	Piece* temp = NULL;
	bool b = Piece::pieceAt(gameboard, { 1, 0 }, temp);

	cout << temp->getPos()[0] << "\n";

	return 0;
}