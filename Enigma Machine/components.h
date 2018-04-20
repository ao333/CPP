#ifndef COMPONENTS_H
#define COMPONENTS_H

// constant representing size of alphabet. Can be changed
const int SIZE = 26;

class Plugboard {
  int config[SIZE];
  int config_size;
public:
  Plugboard (char* file);
  void encrypt(int& buffer);
};

class Reflector {
  int config[SIZE*2];
  int config_size;
public:
  Reflector (char* file);
  void encrypt(int& buffer);
};

class Rotor {
  int config[SIZE*2], config_size, rel_config[SIZE], notch[SIZE], notch_count;
  Rotor *leftrotor;
  // check if rotor rotated and if notch is in top pos
  bool is_notch(int position);
 public:
  Rotor(int rotor_number, int _start_pos, char* rot_file, char* pos_file);
  void set_left_rotor(Rotor *rotor_ptr);
  void print_config();
  // rotate the rotor and change relative configuration
  void rotate();
  // Method to encrypt incoming plugboard and outgoing reflector buffer
  void encrypt_plug(int &buffer);
  void encrypt_ref(int &buffer);
};

#endif
