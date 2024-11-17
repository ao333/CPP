#include <iostream>
#include "ChessBoard.h"

ChessBoard::ChessBoard() {
	resetBoard();
}

// reset every piece, player and turn to initial values
void ChessBoard::resetBoard() {
	// deletes all values from the board map
	for (map<string, Piece*>::iterator it = board_map.begin(); it != board_map.end(); it++)
		delete it->second;
	board_map.clear();
	// initialize all board map squares to NULL
	string coordinate;
	for (char file = 'A'; file <= 'H'; file++)
		for (char rank = '1'; rank <= '8'; rank++) {
			coordinate = string() + file + rank;
			board_map[coordinate] = NULL;
		}

	// create every piece at their starting coordinates
	board_map["E1"] = new King(WHITE);
	board_map["E8"] = new King(BLACK);
	board_map["A1"] = new Rook(WHITE);
	board_map["H1"] = new Rook(WHITE);
	board_map["A8"] = new Rook(BLACK);
	board_map["H8"] = new Rook(BLACK);
	board_map["C1"] = new Bishop(WHITE);
	board_map["F1"] = new Bishop(WHITE);
	board_map["C8"] = new Bishop(BLACK);
	board_map["F8"] = new Bishop(BLACK);
	board_map["D1"] = new Queen(WHITE);
	board_map["D8"] = new Queen(BLACK);
	board_map["B1"] = new Knight(WHITE);
	board_map["G1"] = new Knight(WHITE);
	board_map["B8"] = new Knight(BLACK);
	board_map["G8"] = new Knight(BLACK);
	board_map["A2"] = new Pawn(WHITE);
	board_map["B2"] = new Pawn(WHITE);
	board_map["C2"] = new Pawn(WHITE);
	board_map["D2"] = new Pawn(WHITE);
	board_map["E2"] = new Pawn(WHITE);
	board_map["F2"] = new Pawn(WHITE);
	board_map["G2"] = new Pawn(WHITE);
	board_map["H2"] = new Pawn(WHITE);
	board_map["A7"] = new Pawn(BLACK);
	board_map["B7"] = new Pawn(BLACK);
	board_map["C7"] = new Pawn(BLACK);
	board_map["D7"] = new Pawn(BLACK);
	board_map["E7"] = new Pawn(BLACK);
	board_map["F7"] = new Pawn(BLACK);
	board_map["G7"] = new Pawn(BLACK);
	board_map["H7"] = new Pawn(BLACK);

	// reset turn to white, and ended game to false
	turn = WHITE;
	ended = false;
	cout << "A new chess game is started!" << endl;
}

// test for various exceptions
bool ChessBoard::test(const string from, const string to) {
	// check if input coordinate is >2 characters
	if (from.size() > 2 || to.size() > 2) {
		cout << "input coordinate is >2 characters\n";
		return false;
	}
	// check if "from" coordinate is out of bounds
	if (from[0] < 'A' || from[0] > 'H' || from[1] < '1' || from[1] > '8') {
		cout << "FROM coordinates out of bound\n";
		return false;
	}
	// check if "to" coordinate is out of bounds
	if (to[0] < 'A' || to[0] > 'H' || to[1] < '1' || to[1] > '8') {
		cout << "TO coordinate is out of bounds\n";
		return false;
	}
	// check if there is actually a piece at "from" coordinate
	if (board_map[from] == NULL) {
		cout << "There is no piece at position " << from << "!\n";
		return false;
	}
	// check if turn is white or black
	if (board_map[from]->player != turn) {
		cout << "It is not " << (turn == WHITE? "Black's " : "White's ") << "turn to move!\n";
		return false;
	}
	// check if moving piece is blocked
	if (!board_map[from]->move(board_map, from, to)) {
		cout << *board_map[from] << " cannot move to " << to << "!\n";
		return false;
	}
	// check if move results in a self-check
	if(selfCheck(from, to, turn)) {
		cout << "Move checks own king\n";
		return false;
	}
	return true;
}

void ChessBoard::submitMove(const string from, const string to) {
	// check if game has ended
	if (ended) {
		cout << "The game has ended.\n";
		return;
	}

	// if move is test, print
	if (test(from, to)) {
		cout << *board_map[from] << " moves from " << from << " to " << to;
		// find and delete captured piece
		if (board_map[to]) {
			map<string, Piece*>::iterator captured_piece;
			captured_piece = board_map.find(to);
			cout << " taking " << *board_map[to];
			delete captured_piece->second;
		}
		cout << endl;

		// move capturing piece to "to", and clear out "from"
		board_map[to] = board_map[from];
		board_map[from] = NULL;
		// warn if current player is in check
		if (check(!turn)) {
			// if checkmate, set ended to true
			if (checkmate(!turn)) {
				cout << (turn == WHITE? "Black" : "White") << " is in checkmate\n";
				ended = true;
				return;
			}
			cout << (turn == WHITE? "Black" : "White") << " is in check\n";
		}

		// check if in stalement
		if (checkmate(!turn)) {
			cout << "stalemate\n";
			ended = true;
			return;
		}

		// change turn
		turn = (turn == WHITE? BLACK : WHITE);
	}
}

// return all legal moves
vector<string> ChessBoard::allMoves (bool current_player) {
	vector<string> piece, all_moves;
	// iterate over all pieces on the board map
	for (map<string, Piece*>::iterator it = board_map.begin(); it != board_map.end(); it++)
		// if it belongs to the current player get all moves for that piece
		if (it->second != NULL && it->second->player == current_player) {
			piece.clear();
			piece = it->second->legalMoves(board_map, it->first);
			all_moves.insert(all_moves.end(), piece.begin(), piece.end());
		}
	return all_moves;
}

// check if opponent is checking you
bool ChessBoard::check(bool current_player) {
	// get all moves of the non-current player
	vector<string> attacks = allMoves(!current_player);
	// if current player's king is in it, current player is in check
	for(vector<string>::iterator it = attacks.begin(); it != attacks.end(); it++)
		if(board_map[*it] != NULL && board_map[*it]->player == current_player && board_map[*it]->type == "King")
			return true;
	// otherwise not in check
	return false;
}

// "look ahead" function to see if next move results in self-check
bool ChessBoard::selfCheck(const string from, const string to, bool current_turn) {
	Piece* captured_temp = NULL;
	// if piece at TO coordinates isn't empty, capture it
	if(board_map[to] != NULL) {
		captured_temp = board_map[to];
	}

	// move piece to from "from" to "to"
	Piece* from_temp = board_map[from];
	board_map[to] = board_map[from];
	board_map[from] = NULL;

	// if in self-checks, move everything back, return true
	if (check(current_turn)) {
		if (captured_temp)
			board_map[to] = captured_temp;
		else
			board_map[to] = NULL;
		board_map[from] = from_temp;
		return true;
	}

	// if not in self-check, move everything back, and return false
	if (captured_temp)
		board_map[to] = captured_temp;
	else
		board_map[to] = NULL;
	board_map[from] = from_temp;

	return false;
}

bool ChessBoard::checkmate(bool current_player) {
	vector<string> piece_moves;
	// iterate over all pieces on the board map
	for(map<string, Piece*>::iterator it = board_map.begin(); it != board_map.end(); it++)
		// if it belongs to the current player get all moves for that piece
		if(it->second != NULL && it->second->player == current_player) {
			piece_moves.clear();
			piece_moves = it->second->legalMoves(board_map, it->first);
			// iterate over all moves
			for (vector<string>::iterator moves = piece_moves.begin(); moves != piece_moves.end(); moves++)
				// if moves made king unchecked, return false for checkmate
				if(!selfCheck(it->first, *moves, !turn))
					return false;
		}
	return true;
}
