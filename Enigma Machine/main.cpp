#include <iostream>
#include "io.h"
#include "components.h"
#include "errors.h"
using namespace std;

int main(int argc, char* argv[]) {
	// Check if the minimum number of arguments is at least 3
	if (argc < 3) {
		cerr << "usage: enigma plugboard-file reflector-file " << "(<rotor-file>* rotor-positions)?" << endl;
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}

	// check plugboard file and create plugboard pointer
	check_file(argv[1]);
	Plugboard *plugboard = new Plugboard(argv[1]);
	// check reflector file and create reflector pointer
	check_file(argv[2]);
	Reflector *reflector = new Reflector(argv[2]);

	int rotor_count = argc-4;
	Rotor** rotors = NULL; /**/
	// if rotors exists, initialize rotor object
	if (rotor_count > 0) {
		// allocate memory to an array of pointers to rotors
		rotors = new Rotor* [rotor_count]; /**/

		int rotor_pos[rotor_count];
		load_pos(rotor_pos, rotor_count, argv[argc-1]);

		for (int i = 0; i < rotor_count; i++) {
			check_file(argv[i+3]);

			rotors[i] = new Rotor(i, rotor_pos[i], argv[i+3], argv[argc-1]);
		}
		// set rotor connections to left rotor
		for (int i = 1; i < rotor_count; i++) {
			rotors[i]->set_left_rotor(rotors[i-1]);
		}
	}

	// encryption
	char input;
	int output;

	cin >> ws;
	while (cin >> input) {
		// check for non-alphabetical or capitalized characters
		if (!isalpha(input) || !isupper(input)) {
			cerr<<input << " is not a valid input character (input " << "characters must be upper case letters A-Z)!" << endl;
			return INVALID_INPUT_CHARACTER;
		} else {
			// convert character input to integer output
			output = (int)(input) - 'A';

			// encrypt plugboard
			plugboard->encrypt(output);

			if (rotor_count > 0) {
				rotors[rotor_count - 1]->rotate();
				for (int i = rotor_count - 1; i >= 0; i--)
					rotors[i]->encrypt_plug(output);
			}
			reflector->encrypt(output);

			if (rotor_count > 0)
				for (int i = 0; i < rotor_count; i++)
					rotors[i]->encrypt_ref(output);

			plugboard->encrypt(output);

			// convert output back to character
			cout << (char)(output + 'A');
		}
	}
	// delete dynamically allocated memory
	delete plugboard;
	delete reflector;
	delete[] rotors;
	return NO_ERROR;
}
