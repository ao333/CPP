#ifndef PIECES_H
#define PIECES_H

#include <map>
#include <string>
#include <vector>
#include "ChessBoard.h"
using namespace std;

class Piece {
public:
	string type;
  bool player;

  Piece(bool player);
  // overload outstream
  friend ostream& operator<<(ostream& o, const Piece& player);
  // virtual function to allow every piece to implement their own moveset vectors
  virtual vector<string> legalMoves(map<string, Piece*> &board_map, string from) = 0;
  bool move(map<string, Piece*> &board_map, string from, string to);
  virtual ~Piece() {}
};

#endif
