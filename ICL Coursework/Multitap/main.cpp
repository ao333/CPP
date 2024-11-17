#include <iostream>
#include <fstream>
#include "multitap.h"
using namespace std;

int main() {

  int size;
  char multitap[512];

  multitap[0] = '\0';

  cout << "====================== Question 1 ======================" << endl << endl;

  size = encode_character('c', multitap);
  cout << "The character 'c' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  size = encode_character('5', multitap);
  cout << "The character '5' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  size = encode_character('Q', multitap);
  cout << "The character 'Q' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  size = encode_character(' ', multitap);
  cout << "The character ' ' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  size = encode_character(',', multitap);
  cout << "The character ',' encoded in multitap is '" << multitap << "' (" << size << " keystrokes)" << endl;

  cout << endl;
  multitap[0] = '\0';

  cout << "====================== Question 2 ======================" << endl << endl;

  encode("imperial", multitap);
  cout << "The string 'imperial' encoded in multitap is '" << multitap << "'" << endl;


  encode("cab", multitap);
  cout << "The string 'cab' encoded in multitap is '" << multitap << "'" << endl;

  encode("Meet Anna at 5pm", multitap);
  cout << "The string 'Meet Anna at 5pm' encoded in multitap is '" << multitap << "'" << endl;

  encode("IiiIiit Is 4am on 2nd Jan 2017", multitap);
  cout << "The string 'IiiIiit Is 4am on 2nd Jan 2017' encoded in multitap is '" << multitap << "'" << endl;

  cout << endl;

  cout << "====================== Question 3 ======================" << endl << endl;

  cout << "Testing decode character" << endl;
  char ch;
  ch = decode_character("444");
  cout << "Decoding '444' gives: " << ch << endl;
  ch = decode_character("6");
  cout << "Decoding '6' gives: " << ch << endl;
  ch = decode_character("9999");
  cout << "Decoding '9999' gives: " << ch << endl;
  ch = decode_character("1");
  cout << "Decoding '1' gives: " << ch << endl;

  ifstream input("message.txt");
  cout << "The plaintext for the multitap encoded message in 'message.txt' is: " << endl;
  decode(input, cout);
  input.close();

  cout << endl;

  return 0;
}
