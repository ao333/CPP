#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own
	 function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char** allocate_2D_array(int rows, int columns) {
	char** m = new char* [rows];
	assert(m);
	for(int r=0; r<rows; r++) {
		m[r] = new char[columns];
		assert(m[r]);
	}
	return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char** m, int rows) {
	for(int r=0; r<rows; r++)
		delete [] m[r];
	delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char* filename, int& height, int& width) {
	char line[512];

	ifstream input(filename);

	height = width = 0;

	input.getline(line, 512);
	while(input) {
		if( (int) strlen(line) > width)
			width = strlen(line);
		height++;
		input.getline(line, 512);
	}

	if(height > 0)
		return true;
	return false;
}

/* pre-supplied function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width) {

	bool success = get_map_dimensions(filename, height, width);

	if(!success) return NULL;

	char** m = allocate_2D_array(height, width);

	ifstream input(filename);

	char line[512];
	char space[] = " ";

	for(int r = 0; r<height; r++) {
		input.getline(line, 512);
		strcpy(m[r], line);
		while( (int) strlen(m[r]) < width ) {
			strcat(m[r], space);
		}
	}

	return m;
}

/* pre-supplied function to print the tube map */
void print_map(char** m, int height, int width) {
	cout << setw(2) << " " << " ";
	for(int c=0; c<width; c++) {
		if(c && (c % 10) == 0) {
			cout << c/10;
		} else {
			cout << " ";
		}
	}

	cout << endl;
	cout << setw(2) << " " << " ";

	for(int c=0; c<width; c++) cout << (c % 10);

	cout << endl;

	for(int r=0; r<height; r++) {
		cout << setw(2) << r << " ";
		for(int c=0; c<width; c++) cout << m[r][c];
		cout << endl;
	}
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char* error_description(int code) {
	switch(code) {
	case ERROR_START_STATION_INVALID:
		return "Start station invalid";
	case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
		return "Route endpoint is not a station";
	case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
		return "Line hopping between stations not possible";
	case ERROR_BACKTRACKING_BETWEEN_STATIONS:
		return "Backtracking along line between stations not possible";
	case ERROR_INVALID_DIRECTION:
		return "Invalid direction";
	case ERROR_OFF_TRACK:
		return "Route goes off track";
	case ERROR_OUT_OF_BOUNDS:
		return "Route goes off map";
	}
	return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char* token) {
	const char* strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
	for(int n=0; n<8; n++) {
		if(!strcmp(token, strings[n])) return (Direction) n;
	}
	return INVALID_DIRECTION;
}

/* Function to find the coordinates (r,c) of the first occurrence
of symbol 'target' on an ASCII map with height rows and width columns when
scanned in a row-by-row fashion. */
bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c){
	int i, j;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			if(map[i][j] == target){
				r = i;
				c = j;
				return true;
			}
		}
	}
	r = -1;
	c = -1;
	return false;
}

/* Function to get the map symbol character of a station or line */
char get_symbol_for_station_or_line(const char name[]){
	ifstream input1("lines.txt");
	char lines[32];
	input1.getline(lines, 32);
	while(input1.good()){
		if(!strcmp(name, &lines[2])){
			input1.close();
			return lines[0];
		}
		input1.getline(lines, 32);
	}
	input1.close();

	ifstream input2("stations.txt");
	char stations[64];
	input2.getline(stations, 64);
	while(input2.good()){
		if(!strcmp(name, &stations[2])){
			input2.close();
			return stations[0];
		}
		input2.getline(stations, 64);
	}
	input2.close();

	//if name[] cannot be found in lines.txt or stations.txt,  return space character
	return ' ';
}

/* Function to determine whether a route is valid */
int validate_route(char** map, int height, int width, const char start_station[], const char route[], char destination[]){
	//if the input start_station name is a line name, or is not valid, return -1: ERROR_START_STATION_INVALID
	char symbol = get_symbol_for_station_or_line(start_station);
	if(isalnum(symbol) == 0) return -1;

	//variable declaration
	Direction path[512];
	int r, c, returnvalue, stepcount = 0, changecount = -1;

	//convert route string to direction array and store the length of direction array into path_length
	int path_length = string_route_to_direction_array(route, path);

	//get the position of start_station and store it in (r, c)
	get_symbol_position(map, height, width, symbol, r, c);

	//loop the action move_forward() until it returns the error code or the path is completed
	//if the path is completed, use changecount to count the number of line changes
	char temp_symbol = ' ';
	while(stepcount < path_length){
		returnvalue = move_forward(map, height, width, r, c, path, stepcount);
		//the error codes of move_forward() is the same as those in validate_route()
		if(returnvalue < 0) return returnvalue;
		if(!isalnum(map[r][c]) && map[r][c] != temp_symbol){
			temp_symbol = map[r][c];
			changecount++;
		}
		stepcount++;
	}

	//if the destination is not a station, return -2: ERROR_ROUTE_ENDPOINT_IS_NOT_STATION
	char destination_symbol = map[r][c];
	if(!isalnum(destination_symbol)) return -2;

	//if the path is completed without any error, return changecount, and set the value of destination.
	ifstream station_input("stations.txt");
	char stations[64];
	station_input.getline(stations, 64);
	while(station_input.good()){
		if(destination_symbol == stations[0]){
			station_input.close();
			strcpy(destination, &stations[2]);
			return changecount;
		}
		station_input.getline(stations, 64);
	}
	station_input.close();

	//just in case something abnormal happens(destination symbol cannot be found in stations.txt), return -2
	return -2;
}

/* Function to convert the route string to Direction enum array, and return the length of Direction array */
int string_route_to_direction_array(const char route[], Direction path[]){
	int i = 0, j = 0, k = 0;
	char onestep[512];
	while(route[i]){
		if(route[i] != ','){
			onestep[j] = route[i];
			j++;
		}
		else{
			onestep[j] = '\0';
			path[k] = string_to_direction(onestep);
			k++;
			j = 0;
		}
		i++;
	}
	onestep[j] = '\0';
	path[k] = string_to_direction(onestep);
	return k + 1;
}

/* Function to describe what happens when moving one step in terms of direction */
int move_forward(char** map, int height, int width, int& r, int& c, Direction path[], int stepcount){
	char current_symbol = map[r][c];

	switch(path[stepcount]){
	case 0: r--; break;
	case 1: r++; break;
	case 2: c--; break;
	case 3: c++; break;
	case 4: r--; c++; break;
	case 5: r--; c--; break;
	case 6: r++; c++; break;
	case 7: r++; c--; break;
	default: return -5;//ERROR_INVALID_DIRECTION
	}

	//if route goes off map, return -7: ERROR_OUT_OF_BOUNDS
	if(r < 0 || c < 0 || r >= height || c >= width) return -7;

	//if step into space area, return -6: ERROR_OFF_TRACK
	char next_symbol = map[r][c];
	if(next_symbol == ' ') return -6;

	//if current position and next position are all lines and different from each other
	//return -3: ERROR_LINE_HOPPING_BETWEEN_STATIONS
	if(current_symbol != next_symbol && !isalnum(current_symbol) && !isalnum(next_symbol)) return -3;

	//if current position is not a station and previous step and this step has contradict directions
	//return -4: ERROR_BACKTRACKING_BETWEEN_STATIONS
	if(!isalnum(current_symbol) && stepcount > 0){
		if(		(path[stepcount - 1] == 0 && path[stepcount] == 1) ||
				(path[stepcount - 1] == 1 && path[stepcount] == 0) ||
				(path[stepcount - 1] == 2 && path[stepcount] == 3) ||
				(path[stepcount - 1] == 3 && path[stepcount] == 2) ||
				(path[stepcount - 1] == 4 && path[stepcount] == 7) ||
				(path[stepcount - 1] == 7 && path[stepcount] == 4) ||
				(path[stepcount - 1] == 5 && path[stepcount] == 6) ||
				(path[stepcount - 1] == 6 && path[stepcount] == 5)) return -4;
	}

	//return 0 if move forward successfully
	return 0;
}
