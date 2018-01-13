#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessBoard.h"
#include "Pieces.h"

class Knight : public Piece {
public:
	Knight(bool player);
	vector<string> legalMoves(map<string, Piece*> &board_map, string from);
	~Knight() {}
};

#endif
