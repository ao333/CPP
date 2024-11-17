#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

#include "river.h"

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
  if (!in)
    return false;

  int start_col = col;
  char line[512];
  in.getline(line,512);
  filter(line);
  while (!in.fail()) {
    for (int n=0; n<strlen(line); n++) {
      if (row >= SCENE_HEIGHT)
	return false;
      if (col >= SCENE_WIDTH)
	break;
      scene[row][col++] = line[n];
    }
    row++;
    col = start_col;
    in.getline(line,512);
    filter(line);
  }
  return true;
}

/* pre-supplied helper function to report the status codes encountered in Question 3 */
const char *status_description(int code) {
  switch(code) {
  case ERROR_INVALID_CANNIBAL_COUNT:
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
char** make_river_scene(const char* left, const char* boat) {
  char **scene = create_scene();
  add_to_scene(scene, 0, 0, "bank.txt");
  add_to_scene(scene, 0, 53, "bank.txt");
  add_to_scene(scene, 3, 30, "sun.txt");
  add_to_scene(scene, 19, 19, "river.txt");
  int len_left=strlen(left);
  int len_boat=strlen(boat);
  int n_M(3), n_C(3), n_B(1);
  for(int i=0; i<len_left; i++) {
    if(left[i]=='M') {
      add_to_scene(scene, 2, 1+6*(3-n_M), "missionary.txt");
      n_M--;
    }
    else if(left[i]=='C') {
      add_to_scene(scene, 11, 1+6*(3-n_C), "cannibal.txt");
      n_C--;
    }
    else if(left[i]=='B') {
      add_to_scene(scene, 17, 19, "boat.txt");
      n_B--;
    }
  }
  for(int i=0; i<len_boat; i++) {
    if(!n_B) {
      if(boat[i]=='M') {
        add_to_scene(scene, 11, 22+6*i, "missionary.txt");
        n_M--;
      }
      else if(boat[i]=='C') {
        add_to_scene(scene, 11, 22+6*i, "cannibal.txt");
        n_C--;
      }
    }
    else {
      if(boat[i]=='M') {
        add_to_scene(scene, 11, 39+6*i, "missionary.txt");
        n_M--;
      }
      else if(boat[i]=='C') {
        add_to_scene(scene, 11, 39+6*i, "cannibal.txt");
        n_C--;
      }
    }
  }
  int count(0);
  while(n_M>0) {
    add_to_scene(scene, 2, 54+6*count, "missionary.txt");
    count++;
    n_M--;
  }
  count=0;
  while(n_C>0) {
    add_to_scene(scene, 11, 54+6*count, "cannibal.txt");
    count++;
    n_C--;
  }
  if(n_B) add_to_scene(scene, 17, 36, "boat.txt");

  return scene;
}

int perform_crossing(char left[], const char* targets) {
  int error=VALID_NONGOAL_STATE;
  int len_left=strlen(left);
  if(len_left>7) return ERROR_INPUT_STREAM_ERROR;
  int len_target=strlen(targets);
  if(len_target>2) return ERROR_INVALID_MOVE;
  int l_M(0), l_C(0), l_B(0);
  int r_M(0), r_C(0);
  int t_M(0), t_C(0);
  for(int i=0; i<len_left; i++) {
    if(left[i]=='M') l_M++;
    else if(left[i]=='C') l_C++;
    else if(left[i]=='B') l_B++;
  }
  for(int i=0; i<len_target; i++) {
    if(targets[i]=='M') t_M++;
    else if(targets[i]=='C') t_C++;
    else return ERROR_INVALID_MOVE;
  }
  if(!l_B) {
    l_M+=t_M;
    l_C+=t_C;
  }
  else {
    l_M-=t_M;
    l_C-=t_C;
  }
  r_M=3-l_M;
  r_C=3-l_C;
  if(l_C<0||r_C<0) return ERROR_INVALID_CANNIBAL_COUNT;
  if(l_M<0||r_M<0) return ERROR_INVALID_MISSIONARY_COUNT;

  if((l_M!=0&&(l_C>l_M))||(r_M!=0&&(r_C>r_M))) error=ERROR_MISSIONARIES_EATEN;
  if(r_M==3) error=VALID_GOAL_STATE;

  strcpy(left,"");
  while(l_M>0) {
    char temp[2]="M";
    strcat(left,temp);
    l_M--;
  }
  while(l_C>0) {
    char temp[2]="C";
    strcat(left,temp);
    l_C--;
  }
  if(l_B) {
    char temp[2]="B";
    strcat(left,temp);
  }

  char** scene=make_river_scene(left, targets);
  cout << "Loading the boat..." << endl;
  print_scene(scene);

  if(l_B) {
    for(int i=0; i<len_left; i++) {
      if(left[i]=='B') {
        char temp[512];
        strcpy(temp, left);
        strncpy(left, temp, i);
        strcat(left, &temp[i+1]);
      }
    }
  }
  if(l_B) left[strlen(left)-1]='\0';
  else {
    int pos=strlen(left);
    left[pos]='B';
    left[pos+1]='\0';
  }

  scene=make_river_scene(left, targets);
  cout << "Crossing the river..." << endl;
  print_scene(scene);

  scene=make_river_scene(left, "");
  cout << "Unloading the boat..." << endl;
  print_scene(scene);

  return error;
}

int play_game() {
  char left[512];
  char target[10];
  int error=VALID_NONGOAL_STATE;
  strcpy(left,"MMMCCCB");
  cout << "The initial state: " << endl;
  char** scene=make_river_scene(left,"");
  print_scene(scene);

  while(error!=ERROR_MISSIONARIES_EATEN&&error!=VALID_GOAL_STATE) {
    cout << "Move: " << endl;
    cin >> target;
    error=perform_crossing(left, target);
  }
  return error;
}

int find_solution(char left[], char answer[]) {
  strcpy(answer,"");
  char prevmove[512]="";
  return find_solution(left, answer, prevmove);
}

int find_solution(char left[], char answer[], char prevmove[]) {
  char move[][512]={"MM","MC","CC","C","M"};
  int error=VALID_NONGOAL_STATE;
  int sol;
  for(int i=0; i<5; i++) {
    char temp[512];
    strcpy(temp, answer);
    error=perform_crossing(left, move[i]);
    if(error==VALID_NONGOAL_STATE&&strcmp(move[i],prevmove)) {
      strcpy(prevmove, move[i]);
      strcat(answer, move[i]);
      strcat(answer, ", ");
      sol=find_solution(left, answer, prevmove);
      if(sol==VALID_GOAL_STATE) return sol;
    }
    else if(error==VALID_GOAL_STATE) {
      strcat(answer, move[i]);
      return error;
    }
    perform_crossing(left, move[i]);
    strcpy(answer, temp);
  }
  return ERROR_BONUS_NO_SOLUTION;
}
