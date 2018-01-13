#include <fstream>
using namespace std;

int encode_character(char ch, char multitap[]);
void encode(const char plaintext[], char multitap[]);
char decode_character(const char multitap[]);
void print_decode(const char* buffer, ostream& out, bool caps);
void decode(istream& in, ostream& out);
