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

char** make_river_scene(const char* left, const char* boat){
	char **scene = create_scene();
	add_to_scene(scene, 0, 0, "bank.txt");
	add_to_scene(scene, 0, 53, "bank.txt");
	add_to_scene(scene, 3, 30, "sun.txt");
	add_to_scene(scene, 19, 19, "river.txt");
	int leftM = 0, leftC = 0, boatM = 0, boatC = 0, boatPos = 1;
	int i = 0, j = 0;
	while(left[i]){
		if(left[i] == 'B') boatPos--;
		if(left[i] == 'C') leftC++;
		if(left[i] == 'M') leftM++;
		i++;
	}
	while(boat[j]){
		if(boat[j] == 'C') boatC++;
		if(boat[j] == 'M') boatM++;
		j++;
	}
	add_to_scene(scene, 17, 19 + 17 * boatPos, "boat.txt");
	int k;
	for(k = 0; k < leftM; k++){
		add_to_scene(scene, 2, 1 + 6 * k, "missionary.txt");
	}
	for(k = 0; k < leftC; k++){
		add_to_scene(scene, 11, 1 + 6 * k, "cannibal.txt");
	}
	for(k = 0; k < 3 - leftM - boatM; k++){
		add_to_scene(scene, 2, 54 + 6 * k, "missionary.txt");
	}
	for(k = 0; k < 3 - leftC - boatC; k++){
		add_to_scene(scene, 11, 54 + 6 * k, "cannibal.txt");
	}
	for(k = 0; k <= 1; k++){
		if(boat[k] == 'C'){
			add_to_scene(scene, 11, 22 + 17 * boatPos + 6 * k, "cannibal.txt");
		}
		if(boat[k] == 'M'){
			add_to_scene(scene, 11, 22 + 17 * boatPos + 6 * k, "missionary.txt");
		}
	}
	return scene;
}

int perform_crossing(char* left, const char* targets){
	int leftM = 0, leftC = 0, boatM = 0, boatC = 0, boatPos = 1;
	int i = 0, j = 0;
	while(left[i]){
		if(left[i] == 'B') boatPos--;
		else if(left[i] == 'C') leftC++;
		else if(left[i] == 'M') leftM++;
		else return ERROR_INPUT_STREAM_ERROR;
		if(leftC > 3) return ERROR_INVALID_CANNIBAL_COUNT;
		if(leftM > 3) return ERROR_INVALID_MISSIONARY_COUNT;
		i++;
	}
	if(!targets[0]) return ERROR_INPUT_STREAM_ERROR;
	while(targets[j]){
		if(j >= 2) return ERROR_INVALID_MOVE;
		if(targets[j] == 'C') boatC++;
		else if(targets[j] == 'M') boatM++;
		else return ERROR_INPUT_STREAM_ERROR;
		j++;
	}

	if (boatPos == 0) {
		leftC = leftC - boatC;
		leftM = leftM - boatM;
		if(leftC < 0) return ERROR_INVALID_CANNIBAL_COUNT;
		if(leftM < 0) return ERROR_INVALID_MISSIONARY_COUNT;
		left[0] = 'B';
		int k;
		for (k = 1; k <= leftC; k++) {
			left[k] = 'C';
		}
		for (k = leftC + 1; k <= leftC + leftM; k++) {
			left[k] = 'M';
		}
		left[leftC + leftM + 1] = '\0';

		cout << "Loading the boat... " << endl;
		char **scene = make_river_scene(left, targets);
		print_scene(scene);
		if (leftC > leftM && leftM > 0) return ERROR_MISSIONARIES_EATEN;

		cout << "Crossing the river... " << endl;
		char temp[8];
		strncpy(temp, &left[1], 8);
		strncpy(left, temp, 8);
		scene = make_river_scene(left, targets);
		print_scene(scene);

		cout << "Unloading the boat... " << endl;
		scene = make_river_scene(left, "");
		print_scene(scene);

		if (leftC < leftM && leftM < 3) return ERROR_MISSIONARIES_EATEN;

		if (left[0]) return VALID_NONGOAL_STATE;
		return VALID_GOAL_STATE;
	}

	else{
		int rightC = 3 - leftC - boatC;
		int rightM = 3 - leftM - boatM;
		if(rightC < 0) return ERROR_INVALID_CANNIBAL_COUNT;
		if(rightM < 0) return ERROR_INVALID_MISSIONARY_COUNT;
		cout << "Loading the boat... " << endl;
		char **scene = make_river_scene(left, targets);
		print_scene(scene);
		if (rightC > rightM && rightM > 0) return ERROR_MISSIONARIES_EATEN;

		cout << "Crossing the river... " << endl;
		char temp[8] = "B";
		strncat(temp, left, 8);
		strncpy(left, temp, 8);
		scene = make_river_scene(left, targets);
		print_scene(scene);

		leftC = leftC + boatC;
		leftM = leftM + boatM;
		if(leftC > 3) return ERROR_INVALID_CANNIBAL_COUNT;
		if(leftM > 3) return ERROR_INVALID_MISSIONARY_COUNT;
		left[0] = 'B';
		int k;
		for (k = 1; k <= leftC; k++) {
			left[k] = 'C';
		}
		for (k = leftC + 1; k <= leftC + leftM; k++) {
			left[k] = 'M';
		}
		left[leftC + leftM + 1] = '\0';

		cout << "Unloading the boat... " << endl;
		scene = make_river_scene(left, "");
		print_scene(scene);

		if (left[0]) return VALID_NONGOAL_STATE;
		return VALID_GOAL_STATE;
	}

}

int play_game(){
	  /* the initial state */
	  cout << "The initial state: "<< endl;
	  char left[8] = "BCCCMMM";
	  char targets[3];
	  char** scene = make_river_scene(left,"");
	  print_scene(scene);
	  int result;
	  while(true){
		  cin >> targets;
		  result = perform_crossing(left, targets);
		  if(result != VALID_NONGOAL_STATE) return result;
	  }
}

int find_solution(char* left, char* answer){
	bool flag = solution(left, answer, "");
	if(flag) return VALID_GOAL_STATE;
	return ERROR_BONUS_NO_SOLUTION;

}

bool solution(char* left, char* answer, const char* lastTargets){
	char temp[10], i[3];
	int result;
	const char* targets[5] = {"C", "M", "CC", "CM", "MM"};
	for(int j = 0; j < 5; j++){
		strcpy(i, targets[j]);
		if(strcmp(i, lastTargets) == 0) continue;
		strncpy(temp, left, 10);
		result = perform_crossing(temp, i);
		if(result == VALID_GOAL_STATE){
			strncpy(answer, i, 2);
			strncpy(left, temp, 10);
			return true;
		}
		else if(result == VALID_NONGOAL_STATE){
			strncpy(answer, i, 2);
			strcat(answer, ",");
			if(solution(temp, &answer[strlen(answer)], i)) return true;
		}
	}
	return false;
}

