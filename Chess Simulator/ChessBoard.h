#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <string>
#include <vector>
#include "king.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
using namespace std;

// 0 is white's turn, 1 is black's turn
enum {WHITE, BLACK};

class ChessBoard {
public:
	// map each piece to its coordinates
	map<string, Piece*> board_map;
	bool turn;
	bool ended;

	ChessBoard();
	void resetBoard();
	bool test(const string from, const string to);
	void submitMove(const string from, const string to);
	vector<string> allMoves(bool currentplayer);
	bool check(bool currentplayer);
	bool selfCheck(const string from, const string to, bool thisturn);
	bool checkmate(bool currentplayer);
	~ChessBoard() {}
};

#endif
