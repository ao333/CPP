#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "io.h"
#include "components.h"
#include "errors.h"
using namespace std;

// check input for errors
void check_file(char* file) {
	ifstream in(file);

	if (!in) {
		cerr << "Error opening config file" << endl;
		exit(ERROR_OPENING_CONFIGURATION_FILE);
	}

	// find file extension
	string ext(file);
	size_t pos = ext.find(".");
	string extension = ext.substr(pos);

	// check for non-numeric inputs
	char check;
	in >> check;
	in >> ws;

	while (in) {
		if (!isdigit(check)) {
			if (!extension.compare(".pb"))
				cerr << "Non-numeric character in plugboard file ";
			else if (!extension.compare(".rf"))
				cerr << "Non-numeric character in reflector file ";
			else if (!extension.compare(".rot"))
				cerr << "Non-numeric character for mapping in rotor file ";
			cerr << file << endl;
			exit(NON_NUMERIC_CHARACTER);
		}
		in >> check;
	}
	in.close();
}

// check and load rotor pos
void load_pos(int *rotor_pos, int rotor_count, char *file) {

	// check input for errors
	ifstream check(file);
	if (!check) {
		cerr << "Error opening config file" << endl;
		exit(ERROR_OPENING_CONFIGURATION_FILE);
	}

	char character;
	check >> character;
	check >> ws;
	while (check) {
		if (!isdigit(character)) {
			cerr << "Non-numeric character in rotor positions file " << file << endl;
			exit(NON_NUMERIC_CHARACTER);
		}
		check >> character;
	}
	check.close();

	// load rotor pos
	ifstream in(file);

	// initialize all rotor pos to -1, or 0 if you'd like
	for (int i = 0; i < rotor_count; i++)
		rotor_pos[i] = -1;

	int config_value, index = 0;
	in >> config_value;
	while (in) {
		// check if index is out of bounds
		if (config_value < 0 || config_value > 25) {
			cerr << "Invalid Index" << endl;
			exit(INVALID_INDEX);
		}

		rotor_pos[index] = config_value;
		index++;
		in >> config_value;
	}
	in.close();
}
