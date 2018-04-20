#include <iostream>
#include <string>

using namespace std;

class RAM {
};

class CPU {
};

class Chassis {
};

class Fan {
};

//#define MAX_CAPACITY 4
const int MAX_CAPACITY = 4;

class SystemBox {
private:
  Chassis cage;
  CPU *processor;
  RAM *dimms[MAX_CAPACITY];
  int number_of_ram_installed;
public:
  SystemBox(CPU *p) : processor(p) {
    for (int n=0; n<MAX_CAPACITY; n++) {
      dimms[n] = NULL;
    }
    number_of_ram_installed = 0;
  }

  bool install_ram(RAM *d) {
    if (number_of_ram_installed >= 4)
      return false;
    dimms[number_of_ram_installed++] = d;
  }
};

class Keyboard {
};

class Mouse {
};

class Monitor {
};

class Workstation {
private:
  string hostname;
  SystemBox box;
  Mouse *mouse;
  Keyboard &kbd;
  int monitors;
  Monitor *monitor[256];
public:
  Workstation(string name, CPU *chip, Keyboard &k) :
    hostname(name), box(chip), kbd(k) {
    mouse = NULL;
  }
};

int main() {
  CPU inteli9;
  Keyboard keys;

  Mouse mymouse;
  
  Workstation swordfish("swordfish", &inteli9, keys);
  return 0;
}
