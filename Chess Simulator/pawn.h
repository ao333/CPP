#ifndef PAWN_H
#define PAWN_H

#include "ChessBoard.h"
#include "Pieces.h"

class Pawn : public Piece {
public:
	Pawn(bool player);
	vector<string> legalMoves(map<string, Piece*> &board_map, string from);
	~Pawn() {}
};

#endif
