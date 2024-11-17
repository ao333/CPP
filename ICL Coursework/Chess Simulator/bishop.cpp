#include "bishop.h"

Bishop::Bishop(bool player) : Piece(player) {
	type = "Bishop";
}

vector<string> Bishop::legalMoves(map<string, Piece*> &board_map, string from) {
	vector<string> moves;
	string coordinate = from;
	int file = 1, rank = 1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;

	// while the piece moves NorthEast, but doesn't hit a piece or go out of bounds, add the coordinate to moves
	while (coordinate[0] <= 'H' && coordinate[1] <= '8' && board_map[coordinate] == NULL) {
		moves.push_back(coordinate);
		file++; rank++;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
	}
	if (coordinate[0] <= 'H' && coordinate[1] <= '8' && board_map[coordinate]->player != player)
		moves.push_back(coordinate);
	file = 1; rank = -1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;

	// SouthEast
	while (coordinate[0] <= 'H' && coordinate[1] >= '1' && board_map[coordinate] == NULL) {
		moves.push_back(coordinate);
		file++; rank--;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
	}
	if (coordinate[0] <= 'H' && coordinate[1] >= '1' && board_map[coordinate]->player != player)
			moves.push_back(coordinate);
	file = -1; rank = 1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;

	// NorthWest
	while (coordinate[0] >= 'A' && coordinate[1] <= '8' && board_map[coordinate] == NULL) {
		moves.push_back(coordinate);
		file--; rank++;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
	}
	if (coordinate[0] >= 'A' && coordinate[1] <= '8' && board_map[coordinate]->player != player) {
		moves.push_back(coordinate);
	}
	file = -1; rank = -1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;

	// SouthWest
	while (coordinate[0] >= 'A' && coordinate[1] >= '1' && board_map[coordinate] == NULL) {
		moves.push_back(coordinate);
		file--; rank--;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
	}
	if (coordinate[0] >= 'A' && coordinate[1] >= '1' && board_map[coordinate]->player != player)
		moves.push_back(coordinate);

	return moves;
}
