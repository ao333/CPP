#ifndef SUDOKU_H
#define SUDOKU_H

/* function declarations */
void load_board(const char* filename, char board[9][9]);
void display_board(char board[9][9]);
bool is_complete(char board[9][9]);
bool make_move(const char pos[2], int digit, char board[9][9]);
bool save_board(const char* filename, char board[9][9]);
void copy(char to[9][9], char from[9][9]);
bool solve_board(char board[9][9]);

#endif
