#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include "river.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new (nothrow) char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new (nothrow) char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* pre-supplied function which creates an empty ASCII-art scene */
char **create_scene() {
  char **scene = allocate_2D_array(SCENE_HEIGHT, SCENE_WIDTH);

  for (int i=0; i<SCENE_HEIGHT; i++)
    for (int j=0; j<SCENE_WIDTH; j++)
      scene[i][j] = ' ';

  return scene;
}

/* pre-supplied function which frees up memory allocated for an ASCII-art scene */
void destroy_scene(char **scene) {
  deallocate_2D_array(scene, SCENE_HEIGHT);
}

/* pre-supplied function which displays an ASCII-art scene */
void print_scene(char **scene) {
  for (int i=0; i<SCENE_HEIGHT; i++) {
    for (int j=0; j<SCENE_WIDTH; j++)
      cout << scene[i][j];
    cout << endl;
  }
}

/* helper function which removes carriage returns and newlines from strings */
void filter(char *line) {
  while (*line) {
    if (*line >= ' ')
      line++;
    else
      *line = '\0';
  }
}

/* pre-supplied function which inserts an ASCII-art drawing stored in a file
   into a given ASCII-art scene starting at coordinates (row,col)  */
bool add_to_scene(char **scene, int row, int col, const char *filename) {

  ifstream in(filename);
  if (!in) return false;

  int start_Col = col;
  char line[512];
  in.getline(line,512);
  filter(line);
  while (!in.fail()) {
    for (int n=0; n<strlen(line); n++) {
      if (row >= SCENE_HEIGHT) return false;
      if (col >= SCENE_WIDTH) break;
      scene[row][col++] = line[n];
    }
    row++;
    col = start_Col;
    in.getline(line,512);
    filter(line);
  }
  return true;
}

/* pre-supplied helper function to report the status codes encountered in Question 3 */
const char *status_description(int code) {
  switch(code) {
  case ERROR_INVALID_CANNIBAl_COUNT:
    return "Invalid cannibal count";
  case ERROR_INVALID_MISSIONARY_COUNT:
    return "Invalid missionary count";
  case ERROR_INVALID_MOVE:
    return "Invalid move";
  case ERROR_MISSIONARIES_EATEN:
    return "The missionaries have been eaten! Oh dear!";
  case ERROR_INPUT_STREAM_ERROR:
    return "Unexpected input stream error";
  case ERROR_BONUS_NO_SOLUTION:
    return "No solution";
  case VALID_GOAL_STATE:
    return "Problem solved!";
  case VALID_NONGOAL_STATE:
    return "Valid state, everything is OK!";
  }
  return "Unknown error";
}

/* insert your functions here */
char** make_river_scene(const char* left, const char* boat){
	char **scene = create_scene();
  add_to_scene(scene, 0, 0, "bank.txt");
	add_to_scene(scene, 0, 53, "bank.txt");
  add_to_scene(scene, 3, 30, "sun.txt");
  add_to_scene(scene, 19, 19, "river.txt");
  int i=0,j=0,l_M=0,l_C=0,boatM=0,boatC=0,b=1;

  while(left[i]){
		if(left[i]=='M') l_M++;
    if(left[i]=='C') l_C++;
    if(left[i]=='B') b--;
		i++;
  }

	while(boat[j]){
		if(boat[j]=='M') boatM++;
		if(boat[j]=='C') boatC++;
		j++;
	}

  add_to_scene(scene, 17, 19+17*b, "boat.txt");

  for(int k=0; k<l_M; k++)
    add_to_scene(scene, 2, 1+6*k, "missionary.txt");

  for(int k=0; k<l_C; k++)
    add_to_scene(scene, 11, 1+6*k, "cannibal.txt");

  for(int k=0; k<3-l_M-boatM; k++)
    add_to_scene(scene, 2, 54+6*k, "missionary.txt");

  for(int k=0; k<3-l_C-boatC; k++)
    add_to_scene(scene, 11, 54+6*k, "cannibal.txt");

  if(b==0){
    for(int k=0; k<boatM; k++)
      add_to_scene(scene, 11, 22+6*k, "missionary.txt");
    for(int k=0; k<boatC; k++)
      add_to_scene(scene, 11, 22+6*k, "cannibal.txt");
  }

  if(b==1){
    for(int k=0; k<boatM; k++)
      add_to_scene(scene, 11, 39+6*k, "missionary.txt");
    for(int k=0; k<boatC; k++)
      add_to_scene(scene, 11, 39+6*k, "cannibal.txt");
  }

  return scene;
}

int perform_crossing(char* left, const char* targets){
  int l_len=strlen(left);
  int t_len=strlen(targets);

  if(l_len>7) return ERROR_INVALID_MOVE;
  if(t_len>2) return ERROR_INVALID_MOVE;
  int l_M=0,r_M=0,t_M=0,l_C=0,r_C=0,t_C=0,b=0;

  for(int i=0, i<l_len; i++){
    if(left[i]=='M') l_M++;
    else if(left[i]=='C') l_C++;
    else if(left[i]=='B') b++;
    else return ERROR_INVALID_MOVE;
  }

  for(int i=0; i<t_len; i++){
    if(targets[i]=='M') t_M++;
    else if(targets[i]=='C') t_C++;
    else return ERROR_INVALID_MOVE;
  }

  if(b==0){
    l_M+=t_M;
    l_C+=t_C;
  }
  else{
    l_M-=t_M;
    l_C-=t_C;
  }


}
