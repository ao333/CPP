#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <vector>

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

bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c) {
	for(r=0; r<height; r++) {
		for(c=0; c<width; c++) {
			if(map[r][c]==target) return true;
		}
	}
	r=c=-1;
	return false;
}

char get_symbol_for_station_or_line(const char* name) {
	ifstream fin("lines.txt");
	char ch=get_symbol_for_station_or_line(name, fin);
	fin.close();
	if(ch==' ') {
		fin.open("stations.txt");
		ch=get_symbol_for_station_or_line(name, fin);
		fin.close();
	}
	return ch;
}

char get_symbol_for_station_or_line(const char* name, ifstream& fin) {
	char fullname[80], temp[80];
	fin.getline(temp, 80);
	strcpy(fullname, &temp[2]);
	if(!strcmp(fullname,name)) return temp[0];
	if(fin.eof()) return ' ';
	return get_symbol_for_station_or_line(name, fin);
}

void get_name_station(char symbol, char fullname[]) {
	ifstream fin("stations.txt");
	get_name_station(symbol, fullname, fin);
	fin.close();
}

void get_name_station(char symbol, char fullname[], ifstream& fin) {
	char temp[80];
	fin.getline(temp, 80);
	if(symbol==temp[0]) {
		strcpy(fullname, &temp[2]);
		return;
	}
	if(fin.eof()) {
		strcpy(fullname, "");
		return;
	}
	return get_name_station(symbol, fullname, fin);
}

int validate_route(char** map, int height, int width, const char* start_station,
	const char* route, char destination[]) {
	int r, c;
	int count(-1);
	char last_line='0'; // dummy (digit to make sure that it will count first line)
	vector<Direction> direct;
	char start=get_symbol_for_station_or_line(start_station);
	bool in_map=get_symbol_position(map, height, width, start, r, c);
	if(!is_station(start)) return ERROR_START_STATION_INVALID;
	if(!convert_to_direction(route, direct)) return ERROR_INVALID_DIRECTION;
	for(int i=0; i<direct.size(); i++) {
		int r_prev=r, c_prev=c;
		proceed_direct(direct[i],r,c);
		if(r>=height||c>=width||r<0||c<0) return ERROR_OUT_OF_BOUNDS;
		if(map[r][c]==' ') return ERROR_OFF_TRACK;
		if(!is_station(map[r_prev][c_prev])&&!is_station(map[r][c])&&
			map[r_prev][c_prev]!=map[r][c]) return ERROR_LINE_HOPPING_BETWEEN_STATIONS;
		if(i!=0&&opposite_direct(direct[i-1],direct[i])) return ERROR_BACKTRACKING_BETWEEN_STATIONS;
		if(!is_station(map[r][c])&&map[r][c]!=last_line) {
			count++;
			last_line=map[r][c];
		}
	}
	if(!is_station(map[r][c])) return ERROR_ROUTE_ENDPOINT_IS_NOT_STATION;
	get_name_station(map[r][c], destination);
	return count; 
}

bool convert_to_direction(const char* route, vector<Direction>& direct) {
	int i(0);
	char temp[3];
	for(int n=0; n<=strlen(route); n++) {
		if(route[n]==','||route[n]=='\0') {
			temp[i]='\0';
			Direction subdirect=string_to_direction(temp);
			if(subdirect==INVALID_DIRECTION) return false;
			direct.push_back(subdirect);
			i=0;
		}
		else temp[i++]=route[n];
	}
	return true;
}

bool is_station(char symbol) {
	return isalpha(symbol)||isdigit(symbol);
}

void proceed_direct(Direction subdirect, int& r, int& c) {
	switch(subdirect) {
	case N:
		r--; return;
	case NE:
		r--; c++; return;
	case E:
		c++; return;
	case SE:
		r++; c++; return;
	case S:
		r++; return;
	case SW:
		r++; c--; return;
	case W:
		c--; return;
	case NW:
		r--; c--; return;
	}
	return;
}

bool opposite_direct(Direction direct1, Direction direct2) {
	return (direct1==N&&direct2==S)||(direct1==S&&direct2==N)||
		(direct1==NE&&direct2==SW)||(direct1==SW&&direct2==NE)||
		(direct1==NW&&direct2==SE)||(direct1==SE&&direct2==NW)||
		(direct1==E&&direct2==W)||(direct1==W&&direct2==E);
}
