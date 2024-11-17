#include "rook.h"

Rook::Rook(bool player) : Piece(player) {
	type = "Rook";
}

vector<string> Rook::legalMoves(map<string, Piece*> &board_map, string from) {
	vector<string> moves;
	string coordinate = from;
	int file = 1, rank = 0;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;

	// while the piece moves East, but doesn't hit a piece or go out of bounds, add the coordinate to moves
	while (coordinate[0] <= 'H' && board_map[coordinate] == NULL) {
		moves.push_back(coordinate);
		file++;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
	}
	// if enemy piece is there, backtrack one file
	if (coordinate[0] <= 'H' && board_map[coordinate]->player != player)
		moves.push_back(coordinate);
	file = -1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;

	// West
	while (coordinate[0] >= 'A' && board_map[coordinate] == NULL) {
		moves.push_back(coordinate);
		file--;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
	}
	if (coordinate[0] >= 'A' && board_map[coordinate]->player != player)
		moves.push_back(coordinate);
	file = 0; rank = 1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;

  // North
	while (coordinate[1] <= '8' && board_map[coordinate] == NULL) {
		moves.push_back(coordinate);
		rank++;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
	}
	if (coordinate[1] <= '8' && board_map[coordinate]->player != player)
		moves.push_back(coordinate);
	file = 0; rank = -1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;

	// south
	while (coordinate[1] >= '1' && board_map[coordinate] == NULL) {
		moves.push_back(coordinate);
		rank--;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
	}
	if (coordinate[1] >= '1' && board_map[coordinate]->player != player)
		moves.push_back(coordinate);

	return moves;
}
