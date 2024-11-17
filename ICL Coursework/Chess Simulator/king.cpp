#include "king.h"

King::King(bool player) : Piece(player) {
	type = "King";
}

// return all king moves
vector<string> King::legalMoves(map<string, Piece*> &board_map, string from) {
	vector<string> moves;
	string coordinate = from;
	// if moving file or rank 1 in any direction does not run into an occupied or enemy piece, update the coordinate
	for (int file = -1; file <= 1; file++) {
		if (from[0] + file < 'A' || from[0] + file > 'H')
			continue;

		for (int rank = -1; rank <= 1; rank++) {
			if (from[1] + rank < '1' || from[1] + rank > '8')
				continue;

			coordinate[0] = from[0] + file;
			coordinate[1] = from[1] + rank;
			if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
				moves.push_back(coordinate);
		}
	}
	return moves;
}
