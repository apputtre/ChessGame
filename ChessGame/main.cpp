#include <iostream>
#include "Piece.h"
#include "Pawn.h"

int main()
{
	vector<Piece> gameboard;
	Pawn p({ 1, 0 }, true);
	gameboard.push_back(p);

	std::cout << "Piece at " << p.getCol() << ", " << p.getRow() << "\n";

	position pos = p.getMoves(gameboard)[0];

	std::cout << pos[0] << ", " << pos[1] << "\n";

	return 0;
}