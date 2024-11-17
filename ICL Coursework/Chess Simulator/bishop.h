#ifndef BISHOP_H
#define BISHOP_H

#include "ChessBoard.h"
#include "Pieces.h"

class Bishop : public Piece {
public:
	Bishop(bool player);
	vector<string> legalMoves(map<string, Piece*> &board_map, string from);
	~Bishop() {}
};

#endif
