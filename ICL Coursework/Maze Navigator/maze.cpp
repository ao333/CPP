#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include "maze.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own
	 function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
	char **m = new char *[rows];
	assert(m);
	for (int r=0; r<rows; r++) {
		m[r] = new char[columns];
		assert(m[r]);
	}
	return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
	for (int r=0; r<rows; r++)
		delete [] m[r];
	delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
	char line[512];

	ifstream input(filename);

	height = width = 0;

	input.getline(line,512);
	while (input) {
		if ( (int) strlen(line) > width)
			width = strlen(line);
		height++;
		input.getline(line,512);
	}
	if (height > 0)
		return true;
	return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

	bool success = get_maze_dimensions(filename, height, width);

	if (!success)
		return NULL;

	char **m = allocate_2D_array(height, width);

	ifstream input(filename);
	char line[512];

	for (int r = 0; r<height; r++) {
		input.getline(line, 512);
		strcpy(m[r], line);
	}
	return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
	cout << setw(4) << " " << " ";
	for (int c=0; c<width; c++)
		if (c && (c % 10) == 0)
			cout << c/10;
		else
			cout << " ";
	cout << endl;

	cout << setw(4) << " " << " ";
	for (int c=0; c<width; c++)
		cout << (c % 10);
	cout << endl;

	for (int r=0; r<height; r++) {
		cout << setw(4) << r << " ";
		for (int c=0; c<width; c++)
			cout << m[r][c];
		cout << endl;
	}
}

bool find_marker(char marker, char **m, int height, int width, int &row, int &column){
	for (int r=0; r<height; r++)
		for (int c=0; c<width; c++)
			if (m[r][c]==marker){
				row=r;
				column=c;
				return true;
			}
	row=-1;
	column=-1;
	return false;
}

bool valid_solution(const char *path, char **m, int height, int width){
	int row,column;

	if(find_marker('>', m, height, width, row, column)){
		for (int i=0; i<strlen(path); i++){
			switch(path[i]){
				case 'N': row--; break;
				case 'S': row++; break;
				case 'E': column++; break;
				case 'W': column--; break;
				default: return false;
			}
			if (row>height || row<0 || column>width || column<0)
				return false;
			if (m[row][column]=='-' || m[row][column]=='+' || m[row][column]=='|')
				return false;
		}
		if (m[row][column]=='X')
			return true;
		return false;
	}
	return false;
}

const char* find_path(char** m, int height, int width, char start, char end){
	// allocate memory for path string
	char* path = new char[512];
	// initiate and end the first character of the string with \0 so it can be concatenated
	path[0] = '\0';

	if (found(m, height, width, start, end, path))
		return path;
	return "no solution";
}

bool found(char** m, int height, int width, char start, char end, char* path){
	//initialize start and end row/column coordinates
	int row, col, rowE, colE;
	bool S = find_marker(start, m, height, width, row, col);
	bool E = find_marker(end, m, height, width, rowE, colE);

	// base case: success if maze end marker is overwritten and therefore cannot be found
	if (!E)
		return true;

	// if north is not out of bounds
	if (row-1 >= 0){
		// if north is the end symbol, overwrite northern and current coordinate with #
		if (m[row-1][col] == end){
			m[row-1][col] = '#';
			m[row][col] = '#';
			//concatenate N into path string, then recurse to base case
			strcat(path, "N");
			return found(m, height, width, start, end, path);
		}
		// else if northern coordinate is a space, overwrite it with the start symbol so the recursion can restart there
		else if (m[row-1][col] == ' '){
			m[row-1][col] = start;
			m[row][col] = '#';
			strcat(path, "N");
			// if function cannot find any empty spaces nearby, return northern coordinate back to space, and current to start
			if(!found(m, height, width, start, end, path)){
				m[row-1][col] = ' ';
				m[row][col] = start;
				// overwrite previous path character with \0 to reverse this step and end the string
				path[strlen(path) - 1] = '\0';
			} else {
				// not a dead end, recurse
				return found(m, height, width, start, end, path);
			}
		}
	}

	// same logic, but for south
	if (row+1 < height){
		if (m[row+1][col] == end){
			m[row+1][col] = '#';
			m[row][col] = '#';
			strcat(path, "S");
			return found(m, height, width, start, end, path);
		}
		else if (m[row+1][col] == ' ') {
			m[row+1][col] = start;
			m[row][col] = '#';
			strcat(path, "S");
			if(!found(m, height, width, start, end, path)) {
				m[row+1][col] = ' ';
				m[row][col] = start;
				path[strlen(path)-1] = '\0';
			} else {
				return found(m, height, width, start, end, path);
			}
		}
	}

	// east
	if (col+1 < width){
		if (m[row][col+1] == end){
			m[row][col+1] = '#';
			m[row][col] = '#';
			strcat(path, "E");
			return found(m, height, width, start, end, path);
		}
		else if (m[row][col+1] == ' '){
			m[row][col+1] = start;
			m[row][col] = '#';
			strcat(path, "E");
			if(!found(m, height, width, start, end, path)){
				m[row][col+1] = ' ';
				m[row][col] = start;
				path[strlen(path)-1] = '\0';
			} else {
				return found(m, height, width, start, end, path);
			}
		}
	}

	// west
	if (col-1 < width){
		if (m[row][col-1] == end) {
			m[row][col-1] = '#';
			m[row][col] = '#';
			strcat(path, "W");
			return found(m, height, width, start, end, path);
		}
		else if (m[row][col-1] == ' '){
			m[row][col-1] = start;
			m[row][col] = '#';
			strcat(path, "W");
			if(!found(m, height, width, start, end, path)) {
				m[row][col-1] =' ';
				m[row][col] = start;
				path[strlen(path)-1] = '\0';
			} else {
				return found(m, height, width, start, end, path);
			}
		}
	}
	// if base case not reached, return false
	return false;
}

// const char* find_path(char** m, int height, int width, char start, char end){
// 	char** wasHere = allocate_2D_array(height, width);
// 	char* path = new char[512];
// 	path[0] = '\0';
//
// 	int row,col,rowE,colE;
// 	bool S = find_marker(start, m, height, width, row, col);
// 	bool E = find_marker(end, m, height, width, rowE, colE);
// 	bool b = recur(row,col,rowE,colE,m,wasHere,path,height,width);
//
// 	if (b)
// 		return path;
// 	return "no solution";
// }
//
// bool recur(int row, int col, int rowE, int colE, char** m, char** wasHere, char* path, int height, int width){
// 	if (row==rowE && col==colE)
// 		return true;
// 	if (m[row][col]=='-' || m[row][col]=='+' || m[row][col]=='|' || wasHere[row][col])
// 		return false;
//
// 	wasHere[row][col]=true;
// 	if (row-1>=0)
// 		if (recur(row-1,col,rowE,colE,m,wasHere,path,height,width)){
// 			strcat(path,"N");
// 			m[row][col]='#';
// 			return true;
// 		}
// 	if (row+1<height)
// 		if (recur(row+1,col,rowE,colE,m,wasHere,path,height,width)){
// 			strcat(path,"S");
// 			m[row][col]='#';
// 			return true;
// 		}
// 	if (col-1>=0)
// 		if (recur(row,col-1,rowE,colE,m,wasHere,path,height,width)){
// 			strcat(path,"W");
// 			m[row][col]='#';
// 			return true;
// 		}
// 	if (col+1<width)
// 		if (recur(row,col+1,rowE,colE,m,wasHere,path,height,width)){
// 			strcat(path,"E");
// 			m[row][col]='#';
// 			return true;
// 		}
// 	return false;
// }

// const char* find_path(char** m, int height, int width, char start, char end){
// 	int row,column;
// 	char pivot;
// 	char* path = new char[512];
// 	path[0]='\0';
//
// 	if(find_marker(start, m, height, width, row, column)){
// 		while (m[row+1][column]==' ' || m[row-1][column]==' ' || m[row][column+1]==' ' || m[row][column-1]==' '){
// 			if (m[row+1][column]==' ' || m[row+1][column]==end){
// 				m[row][column]='#';
// 				m[++row][column]='#';
// 				strcat(path,"S");
// 			}
// 			if (m[row-1][column]==' ' || m[row-1][column]==end){
// 				m[row][column]='#';
// 				m[--row][column]='#';
// 				strcat(path,"N");
// 			}
// 			if (m[row][column+1]==' ' || m[row][column+1]==end){
// 				m[row][column]='#';
// 				m[row][++column]='#';
// 				strcat(path,"E");
// 			}
// 			if (m[row][column-1]==' ' || m[row][column-1]==end){
// 				m[row][column]='#';
// 				m[row][--column]='#';
// 				strcat(path,"W");
// 			}
// 			if
// 		}
// 		if (m[row+1][column]!=end || m[row-1][column]!=end || m[row][column+1]!=end || m[row][column-1]!=end)
// 			cout << "no solution\n";
// 		return path;
// 	}
// }
