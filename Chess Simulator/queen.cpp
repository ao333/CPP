#include "queen.h"

Queen::Queen(bool p) : Piece(p) {type = "Queen";
	// queen's moveset combines rook and bishop
	rook = new Rook(p);
	bishop = new Bishop(p);
}

vector<string> Queen::legalMoves(map<string, Piece*> &board_map, string from) {
	vector<string> moves;
	moves = rook->legalMoves(board_map, from);
	vector<string> bishops = bishop->legalMoves(board_map, from);
	moves.insert(moves.end(), bishops.begin(), bishops.end());

	return moves;
}
