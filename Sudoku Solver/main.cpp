#include <iostream>
#include <cstdio>
#include "sudoku.h"
using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;

  load_board("easy.dat", board);

  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board))
    cout << "NOT ";
  cout << "a valid move." << endl;

  cout << "Putting 'A' into A1 is ";
  if (!make_move("A1", 'A', board))
    cout << "NOT ";
  cout << "a valid move, because input has to be digit." << endl;

  cout << "Putting '7' into J2 is ";
  if (!make_move("J2", '7', board))
    cout << "NOT ";
  cout << "a valid move, J is out of bounds." << endl;

  cout << "Putting '4' into B10 is ";
  if (!make_move("B10", '4', board))
    cout << "NOT ";
  cout << "a valid move, 10 is out of bounds." << endl;

  cout << "Putting '5' into 7H is ";
  if (!make_move("7H", '5', board))
    cout << "NOT ";
  cout << "a valid move, because 5 is already in the row." << endl;

  cout << "Putting '8' into D5 is ";
  if (!make_move("D5", '8', board))
    cout << "NOT ";
  cout << "a valid move." << endl;

  cout << "Putting '8' into D6 is ";
  if (!make_move("D5", '8', board))
    cout << "NOT ";
  cout << "a valid move, because 6 is already in the column." << endl;

  cout << "Putting '5' into E3 is ";
  if (!make_move("E3", '5', board))
    cout << "NOT ";
  cout << "a valid move." << endl;

  cout << "Putting '3' into E3 is ";
  if (!make_move("E3", '3', board))
    cout << "NOT ";
  cout << "a valid move, because 3 is already in the subboard" << endl;

  display_board(board);

  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << "====================== Question 4 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  cout << "====================== Question 5 ======================" << endl << endl;

  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  } else
  cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
  } else
  cout << "A solution cannot be found." << endl;
  cout << endl;
  display_board(board);

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  return 0;
}
