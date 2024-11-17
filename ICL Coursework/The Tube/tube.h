enum Direction {N, S, W, E, NE, NW, SE, SW, INVALID_DIRECTION};

/* error codes for Question 3 */
#define ERROR_START_STATION_INVALID -1
#define ERROR_ROUTE_ENDPOINT_IS_NOT_STATION -2
#define ERROR_LINE_HOPPING_BETWEEN_STATIONS -3
#define ERROR_BACKTRACKING_BETWEEN_STATIONS -4
#define ERROR_INVALID_DIRECTION -5
#define ERROR_OFF_TRACK -6
#define ERROR_OUT_OF_BOUNDS -7

/* pre-supplied function to load a tube map from a file*/
char** load_map(const char* filename, int& height, int& width);

/* pre-supplied function to print the tube map */
void print_map(char** m, int height, int width);

/* pre-supplied helper function to describe errors for Question 3 */
const char* error_description(int code);

/* presupplied helper function for converting string to Direction enum */
Direction string_to_direction(const char* token);

/* Function to find the coordinates (r,c) of the first occurrence
of symbol 'target' on an ASCII map with height rows and width columns when
scanned in a row-by-row fashion. */
bool get_symbol_position(char** map, int height, int width, char target, int& r, int& c);

/* Function to get the map symbol character of a station or line*/
char get_symbol_for_station_or_line(const char name[]);

/* Function to determine whether a route is valid */
int validate_route(char** map, int height, int width, const char start_station[], const char route[], char destination[]);

/* Function to convert the route string to Direction enum array, and return the length of Direction array */
int string_route_to_direction_array(const char route[], Direction path[]);

/* Function to describe what happens when moving one step in terms of direction */
int move_forward(char** map, int height, int width, int& r, int& c, Direction path[], int stepcount);
