#include <iostream>
#include "ChessBoard.h"
#include "Pieces.h"

Piece::Piece(bool p) {
  player = p;
}

// overload outstream
ostream& operator<<(ostream& o, const Piece& p) {
    	return o << (p.player == WHITE? "White's " : "Black's ") << p.type;
}

// iterate through all possible moves, and if TO is there, return true, if not, return false
bool Piece::move(map<string, Piece*> &board_map, string from, string to) {
	vector<string> moves = legalMoves(board_map, from);
	for(vector<string>::iterator it = moves.begin(); it != moves.end(); it++)
		if(*it == to)
			return true;

	return false;
}
