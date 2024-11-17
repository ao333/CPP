#include <iostream>
#include <fstream>
#include <cstdlib>
#include "components.h"
#include "errors.h"
using namespace std;

// Plugboard Class Constructor
Plugboard::Plugboard(char* file) {

	// Initialize all config indexes to -1, a meaningless value. 0 also works.
	for (int i = 0; i < SIZE; i++)
		config[i] = -1;

	ifstream in(file);
	config_size = 0;
	int config_value;

	// check for if value is out of bounds
	in >> config_value;
	while (in) {
		if (config_value < 0 || config_value > 25) {
			cerr << "Invalid Index in plugboard file " << file << endl;
			exit(INVALID_INDEX);
		}
		config[config_size] = config_value;
		config_size++;
		in >> config_value;
	}

	// check for odd numbers and out of bound parameters
	if (config_size % 2 == 1 || config_size > SIZE) {
		cerr << "Incorrect number of parameters in plugboard file " << file << endl;
		exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
	}

	// check for duplicate configs in plugboard file
	for (int i = 0; i < config_size; i++) {
		for (int j = 0; j < config_size; j++) {
			if (i != j)
				if (config[i] == config[j]) {
					cerr << "Impossible plugboard configuration" << endl;
					exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
				}
		}
	}
	in.close();
}

// encrypt plugboard //
void Plugboard::encrypt(int& buffer) { /**/

	if (config_size == 0)
		return;

	if (buffer == config[config_size -1]) {
		buffer = config[config_size -2];
	} else {
		for (int i = 0; i < config_size - 1; i++) {
			if (buffer == config[i]) {
				if (i % 2 == 0) {
					buffer = config[i+1];
					break;
				} else {
					buffer = config[i-1];
					break;
				}
			}
		}
	}
}

// Plugboard Class Constructor
Reflector::Reflector(char* file) {

	// Initialize all config indexes to -1, a meaningless value. 0 also works.
	for (int i = 0; i < SIZE; i++)
		config[i] = -1;

	ifstream in(file);
	config_size = 0;
	int config_value;

	// check for invalid index
	in >> config_value;
	while(in) {
		if (config_value < 0 || config_value > 25) {
			 cerr << "Invalid Index" << endl;
			 exit(INVALID_INDEX);
		}
		config[config_size] = config_value;
		config_size++;
		in >> config_value;
	}

	// check for odd numbers and out of bound parameters
	if (config_size % 2 == 1) {
		cerr << "Incorrect (odd) number of parameters in reflector file " << file << endl;
		exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
	}

	// check if number of configs is not 26
	if (config_size != SIZE) {
		cerr << "Insufficient number of mappings in reflector file: " << file << endl;
		exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
	}

	// check for duplicate configs in reflector file
	for (int i = 0; i < config_size; i++) {
		for (int j = 0; j < config_size; j++) {
			if (i != j)
				if (config[i] == config[j]) {
					cerr << "Invalid reflector config." << endl;
					exit(INVALID_REFLECTOR_MAPPING);
				}
			}
	}
	in.close();
}

// encrypt reflector
void Reflector::encrypt(int& buffer) {

	if (buffer == config[config_size -1]) {
		buffer = config[config_size - 2];
	} else {
		for (int i = 0; i < config_size - 1; i++) {
			if (buffer == config[i]) {
				if (i % 2 == 0) {
					buffer = config[i+1];
					break;
				} else {
					buffer = config[i-1];
					break;
				}
			}
		}
	}
}

// constructor for rotor class
Rotor::Rotor (int rotor_number, int start_pos, char* rot_file, char* pos_file)
{
	if (start_pos == -1) {
		cerr << "No starting position for rotor " << rotor_number << " in rotor position file: " << pos_file << endl;
		exit(NO_ROTOR_STARTING_POSITION);
	}

  // load rotor file
	ifstream in(rot_file);
	for (int i = 0; i < SIZE*2; i++)
		config[i] = -1;

	int config_value;
	config_size = 0;

	in >> config_value;
	while(in) {
		// checks if config value is out of bounds
		if (config_value < 0 || config_value > 25) {
			cerr << "Invalid Index" << endl;
			exit(INVALID_INDEX);
		}

		config[config_size] = config_value;
		config_size++;
		in >> config_value;
	}

	// check number of inputs
	if (config_size < SIZE) {
		cerr << "Not all inputs mapped in rotor file: " << rot_file << endl;
		exit(INVALID_ROTOR_MAPPING);
	}

	// check for duplicate configs
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i != j) {
				if (config[i] == config[j]) {
					cerr << "Invalid mapping of input " << j << " to output " << config[i] << " (output " << config[i];
					cerr << " is already mapped to from input " << i << ") " << endl;
					exit(INVALID_ROTOR_MAPPING);
				}
			}
		}
	}
	in.close();


	// set relative starting position
	int index = 0;
	for (int i = start_pos; i < SIZE; i++) {
		rel_config[index] = config[i];
		index++;
	}

	for (int i = index; i < SIZE; i++)
		rel_config[i] = config[i - index];

	// decrement relative positions by starting position to get actual encryption
	for (int i = 0; i < SIZE; i++) {
		if (rel_config[i] - start_pos < 0)
			rel_config[i] = SIZE + (rel_config[i] - start_pos);
		else
			rel_config[i] -= start_pos;
	}

	// initialize and set notch from rotor file
	notch_count = 0;
	for (int i = SIZE; i < SIZE*2; i++) {
		if (config[i] != -1) {
			notch[i - SIZE] = config[i];
			notch_count++;
		} else {
			break;
		}
	}

	// Similarly, turn all position of notch into indices /**/
	for (int i = 0; i < notch_count; i++) {
		notch[i] = config[notch[i]];
		if (notch[i] - start_pos < 0)
			notch[i] = SIZE + (notch[i] - start_pos);
		else
			notch[i] -= start_pos;
	}
	leftrotor = NULL;
}

// set left rotor
void Rotor::set_left_rotor(Rotor *rotor_ptr) {
	leftrotor = rotor_ptr;
}
// rotate the rotor 1 step
void Rotor::rotate() {
	// Rotate relative configuration by swapping elements within array
	int temp;
	for (int i = 0; i < 25; i++) {
		temp = rel_config[i];
		rel_config[i] = rel_config[i+1];
		rel_config[i+1] = temp;
	}
	// decrement relative configs by 1 to represent actual config
	for (int i = 0; i < SIZE; i++) {
		if ( rel_config[i] - 1 < 0)
			rel_config[i] = SIZE + (rel_config[i] - 1);
		else
			rel_config[i] -= 1;
	}

	// decrement notch configs by 1 to represent actual notch config
	for (int i = 0; i < notch_count; i++) {
		if ( notch[i] - 1 < 0)
			notch[i] = SIZE + (notch[i] - 1);
		else
			notch[i] -= 1;
	}

	// if top position is a notch, rotate left rotor
	if (is_notch(rel_config[0])) {
		leftrotor->rotate();
	}
}

// check if current pos is a notch
bool Rotor::is_notch(int position) {
	// check if left rotor exists
	if (!leftrotor)
		return false;

	// is a notch when indicies line up to the top position, else not a notch
	for (int i = 0; i < notch_count; i++) {
		if (position == notch[i])
			return true;
	}
	return false;
}

// encrypt incoming buffer from plugboard /**/
void Rotor::encrypt_plug(int& plug_buf) {
	for (int i = 0; i < SIZE; i++) {
		if (plug_buf == i) {
			plug_buf = rel_config[i];
			break;
		}
	}
}

// encrypt outgoing buffer to reflector /**/
void Rotor::encrypt_ref(int& ref_buffer) {
	for (int i = 0; i < SIZE; i++) {
		if (ref_buffer == rel_config[i]) {
			ref_buffer = i;
			break;
		}
	}
}
