#ifndef ROOK_H
#define ROOK_H

#include "ChessBoard.h"
#include "Pieces.h"

class Rook : public Piece {
public:
	Rook(bool player);
	vector<string> legalMoves(map<string, Piece*> &board_map, string from);
	~Rook() {}
};

#endif
