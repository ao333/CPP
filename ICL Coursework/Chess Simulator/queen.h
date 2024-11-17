#ifndef QUEEN_H
#define QUEEN_H

#include "ChessBoard.h"
#include "Pieces.h"

class Rook;
class Bishop;
class Queen : public Piece {
public:
	Rook* rook;
	Bishop* bishop;

	Queen(bool player);
	vector<string> legalMoves(map<string, Piece*> &board_map, string from);
	~Queen() {}
};

#endif
