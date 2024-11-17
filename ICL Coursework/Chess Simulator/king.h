#ifndef KING_H
#define KING_H

#include "ChessBoard.h"
#include "Pieces.h"

class King : public Piece {
public:
	King(bool p);
	vector<string> legalMoves(map<string, Piece*> &board_map, string from);
	~King() {}
};

#endif
