#pragma once

#include <array>
#include <vector>
#include "chessdefs.h"
#include "Piece.h"
#include "Chessboard.h"

class Knight : public Piece
{

public:
	Knight(PlayerColor color);

	std::vector<move> getMoves(Chessboard& board) override;

};
