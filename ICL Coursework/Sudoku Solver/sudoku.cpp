#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }
  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* Pre-supplied function to display a Sudoku board */
void display_board(char board[9][9]){
  cout<<"    ";
  for(int r=0;r<9;r++)
    cout<<(char)('1'+r)<<"   ";
  cout<<endl;
  for(int r=0;r<9;r++){
    if(!(r%3))
      cout << "  +===========+===========+===========+"<<endl;
    else
      cout << "  +---+---+---+---+---+---+---+---+---+"<<endl;
    cout<<(char)('A'+r)<<" ";
    for(int c=0;c<9;c++){
      cout<<((c%3)?':':'|')<<" ";
      cout<<((board[r][c]=='.')?' ':board[r][c])<<" ";
    }
    cout<<"|"<<endl;
  }
  cout<<"  +===========+===========+===========+"<<endl<<endl;
}

/* add your functions here */
bool is_complete(char board[9][9]){
  for(int r=0;r<9;r++)
    for(int c=0;c<9;c++)
      if(!isdigit(board[r][c]))
        return false;

  return true;
}

bool make_move(const char pos[2], int digit, char board[9][9]){
  int r=pos[0]-'A',c=pos[1]-'0'-1;

  if(!isdigit(digit))
    return false;
  if(r<0||r>9||c<0||r>9)
    return false;

  for(int i=0;i<9;i++){
    if(board[r][i]==digit)
      return false;
  }
  for(int j=0;j<9;j++){
    if(board[j][c]==digit)
      return false;
  }

  int sr=r-(r%3);
  int sc=c-(c%3);
  for(int x=sr,n=sr+3;x<n;x++)
    for(int y=sc,m=sc+3;y<m;y++)
      if(board[x][y]==digit)
	      return false;

  board[r][c]=digit;
  return true;
}

bool save_board(const char* filename, char board[9][9]){
  ofstream output(filename);
  if(!output){
    return false;
  }
  for(int r=0;r<9;r++){
    for(int c=0;c<9;c++){
      output<<board[r][c];
    }
    output<<endl;
  }
  output.close();
  return true;
}

void copy(char to[9][9],char from[9][9]){
  for(int row=0;row<9;row++)
    for (int col=0;col<9;col++)
      to[row][col]=from[row][col];
}

bool solve_board(char board[9][9]){
  // counts number of recursion
  static int counter=0;
  counter++;

  if(is_complete(board))
    return true;
  else{
    char new_board[9][9];
    copy(new_board,board);

    char digit='0';
    char pos[]="A1";
    for(int row=0;row<9;row++)
      for(int col=0;col<9;col++){
        pos[0]='A'+row;
        pos[1]='1'+col;
        // skips cells that are occupied
        if(isdigit(new_board[row][col]))
          continue;
        // otherwise, find appropriate digit by iteration
        for(int n=1;n<=9;n++){
          digit='0'+n;
          // if a move could be made
          if(make_move(pos,digit,new_board))
            // tries to solve it using the current digit and checks if board is complete by recursively calling itself
            if(solve_board(new_board)){
              // board has been solved, copies solution to original and returns true
              copy(board,new_board);

              if(counter!=0)
                cout<<counter<<" recursions"<<endl;

              counter=0;
              return true;
	          }
	      }
      	// exhausted all moves for current try, return false to return control to previous stack call
      	// so it could iterate over other digits for previous cells
	      return false;
      }
    return false;
  }
}
