#include "knight.h"

Knight::Knight(bool player) : Piece(player) {
	type = "Knight";
}

vector<string> Knight::legalMoves(map<string, Piece*> &board_map, string from) {
	vector<string> moveset;
	string coordinate = from;
	// if North right L shape is within board map, add coordinate to move
	int file = 1, rank = 2;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;
	if(from[0] + file <= 'H' && from[1] + rank <= '8') {
		if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	// North down
	file = -1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;
	if(from[0] + file >= 'A' && from[1] + rank <= '8') {
		if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	// East up
	file = 2; rank = 1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;
	if(from[0] + file <= 'H' && from[1] + rank <= '8') {
		if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	// West up
	file = -2;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;
	if(from[0] + file >= 'A' && from[1] + rank <= '8') {
		if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	// West down
	rank = -1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;
	if(from[0] + file >= 'A' && from[1] + rank >= '1') {
		if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	//East down
	file = 2;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;
	if(from[0] + file <= 'H' && from[1] + rank >= '1') {
		if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	// South down
	file = -1; rank = -2;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;
	if(from[0] + file >= 'A' && from[1] + rank >= '1') {
		if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	// South up
	file = 1;
	coordinate[0] = from[0] + file;
	coordinate[1] = from[1] + rank;
	if(from[0] + file <= 'H' && from[1] + rank >= '1') {
		if (board_map[coordinate] == NULL || board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	return moveset;
}
