#include "pawn.h"

Pawn::Pawn(bool player) : Piece(player) {
	type = "Pawn";
}

vector<string> Pawn::legalMoves(map<string, Piece*> &board_map, string from) {
	vector<string> moveset;
	string coordinate = from;
	int file, rank;

	// if player is white, and no obstruction, move north one square
	if (player == WHITE) {
		file = 0; rank = 1;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
		if (from[1] + rank <= '8' && board_map[coordinate] == NULL) {
			moveset.push_back(coordinate);
			// if at starting position, move north 2 squares instead
			if (from[1] == '2') {
				rank = 2;
				coordinate[0] = from[0] + file;
				coordinate[1] = from[1] + rank;
				if (board_map[coordinate] == NULL)
					moveset.push_back(coordinate);
			}
		}

		// If North diagonal squares are obstructed by enemy piece, add to moveset (capture implemented in ChessBoard)
		rank = 1; file = 1;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
		if (from[1] + rank <= '8' && from[0] + file <= 'H' && board_map[coordinate] && board_map[coordinate]->player != player)
			moveset.push_back(coordinate);

		file = -1;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
		if (from[1] + rank <= '8' && from[0] + file >= 'A' && board_map[coordinate] && board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}

	// same thing, but for black
	if (player == BLACK) {
		file = 0; rank = -1;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;

		if (from[1] + rank >= '1' && board_map[coordinate] == NULL) {
			moveset.push_back(coordinate);

			if (from[1] == '7') {
				rank = -2;
				coordinate[0] = from[0] + file;
				coordinate[1] = from[1] + rank;

				if (board_map[coordinate] == NULL)
					moveset.push_back(coordinate);
			}
		}

		file = 1; rank = -1;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
		if (from[1] + rank >= '1' && from[0] + file <= 'H' && board_map[coordinate] && board_map[coordinate]->player != player)
			moveset.push_back(coordinate);

		file = -1;
		coordinate[0] = from[0] + file;
		coordinate[1] = from[1] + rank;
		if (from[1] + rank >= '1' && from[0] + file >= 'A' && board_map[coordinate] && board_map[coordinate]->player != player)
			moveset.push_back(coordinate);
	}
	return moveset;
}
