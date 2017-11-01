#include "tube.h"
#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

/* This code illustrates the use of the pre-supplied helper functions and the functions that you are supposed to write.*/
int main() {
	char** map;
	int height, width;

	/* loads the map from the file "map.txt" and sets height and width */
	cout << "Loading tube map with load_map():";
	map = load_map("map.txt", height, width);
	assert(map);
	cout << " done (height = " << height << ", width = " << width << ")." << endl;

	/* prints the map with row and column numbers */
	cout << "Printing map with print_map():" << endl;
	print_map(map,height,width);
	cout << endl;

	cout << "=================== Question 1 ===================" << endl << endl;

	int r, c;
	cout << "The symbol 'T' is ";
	if(get_symbol_position(map, height, width, 'T', r, c))
		cout << "found at (" << r << "," << c << ")";
	else
		cout << "not found.";
	cout << endl << endl;

	cout << "The symbol '4' is ";
	if(get_symbol_position(map, height, width, '4', r, c))
		cout << "found at (" << r << "," << c << ")";
	else
		cout << "not found.";
	cout << endl << endl;

	cout << "The symbol 'z' is ";
	if(get_symbol_position(map, height, width, 'z', r, c))
		cout << "found at (" << r << "," << c << ")";
	else
		cout << "not found.";
	cout << endl << endl;

	cout << "=================== Question 2 ===================" << endl << endl;

	cout << "The symbol for Victoria station is '" <<
		get_symbol_for_station_or_line("Victoria") << "'" << endl << endl;

	cout << "The symbol for Oxford Circus station is '" <<
		get_symbol_for_station_or_line("Oxford Circus") << "'" << endl << endl;

	cout << "The symbol for the District Line is '" <<
		get_symbol_for_station_or_line("District Line") << "'" << endl << endl;

	/* Birmingham station is not on the Tube map, so this should return ' ' */
	cout << "The symbol for Birmingham station is '" <<
		get_symbol_for_station_or_line("Birmingham") << "'" << endl << endl;

	cout << "====================== Question 3 ==================" << endl << endl;

	char route[512];
	char destination[512] = "nowhere";

	/* valid route to Leicester Square with 1 line change */
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Oxford Circus and taking the steps:" << endl;
	cout << route << endl;
	int result = validate_route(
			map, height, width, "Oxford Circus", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/*2 line changes*/
	strcpy(route, "NE,NE,NE,NE,NE,NE,E,E,S,S,S,S,S,S,W,W,W,W");
	cout << "Starting at South Kensington and taking the steps:" << endl << route << endl;
	result = validate_route(map, height, width, "South Kensington", route, destination);
	if(result >= 0)
		cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
	else
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	cout << endl;

	/*A line name is placed instead of a station name, should return invalid station*/
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,E");
	cout << "Starting at Piccadilly Line and taking the steps:" << endl << route << endl;
	result = validate_route(map, height, width, "Piccadilly Line", route, destination);
	if(result >= 0)
		cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
	else
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	cout << endl;

	/*a non-directional character 'z' is placed in the route, should return invalid direction*/
	strcpy(route, "S,SE,S,S,E,E,E,E,E,E,E,E,E,E,z");
	cout << "Starting at Oxford Circus and taking the steps:" << endl << route << endl;
	result = validate_route(map, height, width, "Oxford Circus", route, destination);
	if(result >= 0)
		cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
	else
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	cout << endl;

	/* invalid route because route goes outside of map bounds */
	strcpy(route, "E,NE,SE,SE,SE");
	cout << "Starting at Marylebone and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(map, height, width, "Marylebone", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result <<
			" line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/*route is in map, but on empty space, should return off track*/
	strcpy(route, "S");
	cout << "Starting at Waterloo and taking the steps:" << endl << route << endl;
	result = validate_route(map, height, width, "Waterloo", route, destination);
	if(result >= 0)
		cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
	else
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	cout << endl;

	/*changes lines inbetween stations, should return line hopping*/
	strcpy(route, "NE,SE,E,E");
	cout << "Starting at South Kensington and taking the steps:" << endl << route << endl;
	result = validate_route(map, height, width, "South Kensington", route, destination);
	if(result >= 0)
		cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
	else
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	cout << endl;

	/* invalid route because of backtracking between stations */
	strcpy(route, "W,W,E,W,W,W");
	cout << "Starting at Sloane Square and taking the steps:" << endl;
	cout << route << endl;
	result = validate_route(
			map, height, width, "Sloane Square", route, destination);
	if(result >= 0) {
		cout << "is a valid route with " << result
			<< " line change(s) ending at " << destination << "." << endl;
	} else {
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	}
	cout << endl;

	/*end route is not a station*/
	strcpy(route, "E,E");
	cout << "Starting at South Kensington and taking the steps:" << endl << route << endl;
	result = validate_route(map, height, width, "South Kensington", route, destination);
	if(result >= 0)
		cout << "is a valid route with " << result << " line change(s) ending at " << destination << "." << endl;
	else
		cout << "is an invalid route (" << error_description(result) << ")" << endl;
	cout << endl;

	return 0;
}
