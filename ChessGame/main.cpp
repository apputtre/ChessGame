#include <iostream>
#include "Piece.h"
#include "Pawn.h"

int main()
{
	vector<Piece> gameboard;
	Pawn p({ 1, 0 }, true);
	gameboard.push_back(p);

	std::cout << "Piece at " << p.getCol() << ", " << p.getRow() << "\n";

	std::array<int, 5> arr = { 1, 2, 3, 4, 5 };
	int to_find[1] = { 5 };

	std::array<int, 5>::iterator it;
	it = std::search(arr.begin(), arr.end(), to_find, to_find + 1);

	cout << "found at " << *it << "\n";



	return 0;
}