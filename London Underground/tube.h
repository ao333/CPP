enum Direction {N, S, W, E, NE, NW, SE, SW, INVALID_DIRECTION};

#define ERROR_START_STATION_INVALID -1
#define ERROR_ROUTE_ENDPOINT_IS_NOT_STATION -2
#define ERROR_LINE_HOPPING_BETWEEN_STATIONS -3
#define ERROR_BACKTRACKING_BETWEEN_STATIONS -4
#define ERROR_INVALID_DIRECTION -5
#define ERROR_OFF_TRACK -6
#define ERROR_OUT_OF_BOUNDS -7

/* function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width);

/* function to print the tube map */
void print_map(char** m, int height, int width);

/* function to describe errors for Question 3 */
const char* error_description(int code);

/* function for converting string to Direction enum */
Direction string_to_direction(const char* token);

/*searches 2 files for matching stations or lines,
and returns relevant symbols if found, or space if not*/
char get_symbol_for_station_or_line(const char* name);

/*same as first part of get_symbol_for_station_or_line, but nessessary for when a
line name is input for a station value, where the aforementioned function would pass*/
char get_station_symbol(const char* name);

//searches for 'target' station. Returns true and coordinates for r, c if found,
//or false and -1 for r, c if not found
bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c);

//Switch statement to update previous coordinates when called with Direction dir
int update_rc(int Direction, int& r, int& c);

//final function to convert symbol to a destination station string
void symbol_to_station(char symbol, char* destination);

/*the function returns the number of line changes and assigns destination to be the station at the end of the route.
If the route is invalid, an error code will be returned instead.*/
int validate_route(char** map, int height, int width, const char* start_station, char* route, char* destination);
