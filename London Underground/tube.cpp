#include "tube.h"
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

/* function which gets the dimensions of a map */
bool get_map_dimensions(const char* filename, int& height, int& width) {
	char line[512];
	height = width = 0;
	ifstream input(filename);

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

/* function which allocates a dynamic 2D array */
char** allocate_2D_array(int rows, int columns) {
	char** m = new char* [rows];

	assert(m);
	for(int r = 0; r < rows; r++) {
		m[r] = new char[columns];
	 	assert(m[r]);
	}
	return m;
}

/* function which deallocates a dynamic 2D array */
void deallocate_2D_array(char** m, int rows) {
	for(int r = 0; r < rows; r++)
		delete [] m[r];
	delete [] m;
}

/* function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width) {
	bool success = get_map_dimensions(filename, height, width);

	if(!success) return NULL;
	char line[512];
	char space[] = " ";
	char** m = allocate_2D_array(height, width);
	ifstream input(filename);

	for(int r = 0; r < height; r++) {
		input.getline(line, 512);
		strcpy(m[r], line);
		while( (int) strlen(m[r]) < width ) {
			strcat(m[r], space);
		}
	}
	return m;
}

/* function to print the tube map */
void print_map(char** m, int height, int width) {

	cout << setw(2) << " " << " ";
	for(int c = 0; c < width; c++) {
		if(c && (c % 10) == 0) cout << c/10;
		else cout << " ";
	}
	cout << endl;
	cout << setw(2) << " " << " ";
	for(int c = 0; c < width; c++)
		cout << (c % 10);
	cout << endl;

	for(int r = 0; r < height; r++) {
		cout << setw(2) << r << " ";
		for(int c = 0; c < width; c++)
			cout << m[r][c];
		cout << endl;
	}
}

/* function to report the errors encountered in Question 3 */
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
		return "Invalid Direction";
	case ERROR_OFF_TRACK:
		return "Route goes off track";
	case ERROR_OUT_OF_BOUNDS:
		return "Route goes off map";
	}
	return "Unknown error";
}

/* function for converting string to Direction enum */
Direction string_to_direction(const char* token) {
	const char* strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
	for(int n = 0; n < 8; n++) {
		if(!strcmp(token, strings[n])) return (Direction) n;
	}
	return INVALID_DIRECTION;
}

//searches 2 files for matching stations or lines, and returns relevant symbols if found, or space if not
char get_symbol_for_station_or_line(const char* name) {
	char line[128];
	char* pch;
	ifstream file1("stations.txt");
	ifstream file2("lines.txt");

	file1.getline(line,128);
	//loops through the entirety of stations.txt until if condition is met
	while(file1){
		pch = strstr(line,name);
		//if strstr returns anything but null, a match is found. Return the first char(symbol) of the line
		if (pch!=NULL) return line[0];
		//if null, no match is found. Get new lines from the file until the file ends
		else file1.getline(line,128);
	}
	//repeat of stations.txt search, but this time for lines.txt
	file2.getline(line,128);
	while(file2){
		pch = strstr(line,name);
		if (pch!=NULL) return line[0];
		else file2.getline(line,128);
		} //if both files are searched and still no match, return space character
	return ' ';
}

/*same as first part of get_symbol_for_station_or_line, but nessessary for when a
line name is input for a station value, where the aforementioned function would pass*/
char get_station_symbol(const char* name) {
	char line[128];
	char* pch;
	ifstream file1("stations.txt");

	file1.getline(line,128);
	while(file1){
		pch = strstr(line,name);
		if (pch!=NULL) return line[0];
		else file1.getline(line,128);
	}
	return ' ';
}

//searches for 'target' station. Returns true and coordinates for r, c if found, or false and -1 for r, c if not found
bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c){
	//loops through each row and column, searching for target, starting from index 0
	for(r = 0; r < height; r++){
		for(c = 0; c < width; c++)
			//if char at map coordinate equals target, r, c sets to them incrementally and returns true
			if(map[r][c] == target) return true;
	}//if target is not found next looping through the entire map, set r, c to -1 and return false
	r = c = -1;
	return false;
}

//Switch statement to update previous coordinates when called with Direction dir
int update_rc(Direction dir, int& r, int& c){
	switch(dir) {
		case N: r--; break;
		//North reduces row by 1;
		case S: r++; break;
		//South increases row by 1;
		case W: c--; break;
		//West decreases column by 1;
		case E: c++; break;
		//East increases column by 1;
		case NE: r--; c++; break;
		//Northeast reduces row by 1 and increases column by 1;
		case NW: r--; c--; break;
		//Northwest reduces row by 1 and column by 1;
		case SE: r++; c++; break;
		//Southeast increases row by 1, and column by 1;
		case SW: r++; c--; break;
		//Southwest increases row by 1, and reduces column by 1;
		default: ERROR_INVALID_DIRECTION;
		//returns invalid direction if dir is none of the cases
	  }
	}

//final function to convert symbol to a destination station string
void symbol_to_station(char symbol, char* destination) {
	char line[128];
	ifstream file1("stations.txt");
	int i = 0;

	file1.getline(line,128);
	while(file1) {
		if(line[0] == symbol) {
			//read from the 3rd character to the end of line
			for (int j = 2; line[j] != '\0'; j++) {
				//input the 3rd character into the first character of destination string
				destination[i] = line[j];
				i++;
			}
		}
		file1.getline(line,128);
	}
	//regardless if the symbol is found, add \0 to the final index of destination station to end it
	destination[i] = '\0';
}



/*the function returns the number of line changes and assigns destination to be the station at the end of the route.
If the route is invalid, an error code will be returned instead.*/
int validate_route(char** map, int height, int width, const char* start_station, char* route, char* destination) {
	int r, c;
	//initilize symbol with start station symbol
	char symbol = get_station_symbol(start_station);
	//return invalid station if symbol is not found in stations.txt
	if(symbol==' ')
		return ERROR_START_STATION_INVALID;
	//returns invalid station if symbol is not found in map.txt
	if(!get_symbol_position(map, height, width, symbol, r, c))
		return ERROR_START_STATION_INVALID;



	//function to parse the route string, or remove the commas. Note that an easier way would be to use strtok
	Direction dir_without_comma[128];
	char comma_to_endline[4];
	int step = 0, j = 0;
	//loop until the end of the route string
	for (int i = 0; route[i] != '\0'; i++){
		//if there is a comma
		if (route[i] == ',') {
			//add a endline value to the temperary string comma_to_endline
			comma_to_endline[j] = '\0';
			//we then put whatever we have remaining in comma_to_endline into dir_without_comma, our destired string
			dir_without_comma[step] = string_to_direction(comma_to_endline);
		//if the stored value is invalid, return invalid direction
		if (dir_without_comma[step] == INVALID_DIRECTION)
			return ERROR_INVALID_DIRECTION;
		//reset the temp string: comma_to_endline index to 0, so we can repeat the process again
		j=0;
		//increment the step, so we can add new elements into our desired string
		step++;
	} else {
			//this is actually our core code: add element from route array into comma_to_endline, if there is no comma
			comma_to_endline[j] = route[i];
			//increment j++ allows us to place the null value in the right place, instead of overwriting actual directions
			j++;
		}
	}
	//repeats the process for the last character of the array
	comma_to_endline[j] = '\0';
	dir_without_comma[step] = string_to_direction(comma_to_endline);
	if (dir_without_comma[step] == INVALID_DIRECTION)
		return ERROR_INVALID_DIRECTION;
	step++;



	//core function for looping through the entire direction string and outputting errors
	char prev_symbol, curr_symbol, next_symbol;
  int prev_r, prev_c, curr_r = r, curr_c = c, next_r = r, next_c = c;
	int change = 0;

  for (int i = 0; i < step; i++) {
		//initialize curr_symbol to current coordinates
    curr_symbol = map[curr_r][curr_c];
    prev_symbol = map[prev_r][prev_c];
		//update next row and column coordinates using parsed direction string
    update_rc(dir_without_comma[i], next_r, next_c);
		//if those coordinates are negative (cannot be found on map) or greater than map height/widgth, return out of bounds
		if (next_r < 0 || next_c < 0 || next_r >= height || next_c >= width)
	    return ERROR_OUT_OF_BOUNDS;
		//initialize next symbol to the updated coordinates
		next_symbol = map[next_r][next_c];
		//if next symbol is not a line or station, we are off track
		if (next_symbol == ' ')
			return ERROR_OFF_TRACK;

		/*Since station symbols are alphanumerical, isalnum will tell us if curr_symbol and next symbol are stations.
		If current and previous symbols are not stations, and they are different, (same means that the train
		is progressing normally), then we are hopping between lines*/
    if (!isalnum(curr_symbol) && !isalnum(next_symbol) && next_symbol != curr_symbol)
			return ERROR_LINE_HOPPING_BETWEEN_STATIONS;



		//function to check for backtracking. The numbers aren't ordered because NE's opposite is SW
    int backtrack_check[] = {1,-1,2,-2,3,4,-4,-3};
      if (i < step-1)
				/*dir_without_comma[] and +1 will return the current and next enum directions. These then serve as the index for
				backtrack_check[]. If for example, the current and next directions are opposite, like N and S, then they will
				make backtrack_check 1, and -1. If that equals 0, then we go in one direction, only to backtrack right after*/
				if (backtrack_check[dir_without_comma[i]] + backtrack_check[dir_without_comma[i+1]] == 0)
	  			return ERROR_BACKTRACKING_BETWEEN_STATIONS;



		/*if curr_symbol is a station, and the next symbol is different from the previous symbol, then we changed lines.
		The i > 0 enforces the condition that we have at least moved one step*/
    if (isalnum(curr_symbol) && next_symbol != prev_symbol && i > 0)
			change++;

		//By displacing older values with current ones, we can progress the loop by getting new values for next row/column
    prev_r = curr_r;
    prev_c = curr_c;
    curr_r = next_r;
    curr_c = next_c;
	}



	//if final symbol is not alphanumerical, then it's not a station
	if (!isalnum(next_symbol))
    return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
	//inputs the station symbol and changes the value of destination, for final output
	symbol_to_station(next_symbol, destination);

	return change;
}
