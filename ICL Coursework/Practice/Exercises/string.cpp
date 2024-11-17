/* Program 6.5.1 from C++ Programming Lecture notes  */

/* This program demonstrates the string functions 
    "getline", "strcpy" and "strcmp" */

#include <iostream>
#include <cstring>

/* similar to cstring function strcpy */
                              
void string_copy(char dest[], const char source[]) {
  int n;
  for (n=0; source[n] != '\0' ; n++) {    
    dest[n] = source[n];
  }
  dest[n] = '\0';
}

/* similar to cstring function strlen */
int string_length(const char str[]) {
  int n;
  for (n=0; str[n] ; n++);
  return n;
}

// cout << string_length("cat");

// const int n = 10;
// char data[n];
// strcpy(data,"cat");
// cout << string_length(data);

#include <cctype>
/* similar to cstring function strcmp */

int string_compare(const char one[], const char two[]) {
  int count;
  for (count = 0; one[count] && two[count] ; count++) {
    if (one[count] < two[count])
      return -1;
    if (one[count] > two[count])
      return 1;
  }
  if (one[count] == two[count])
    return 0;
  return (one[count] < two[count]) ? -1 : 1; // ternary expression
}

using namespace std;

const int MAXIMUM_LENGTH = 80;

void print_string(char str[]) {
  for (int n=0; str[n]!='\0' ; n++)
    cout << str[n];

  cout << endl;
}

int main()
{

  char phrase[20] = "Enter your name:";
  cout << phrase << endl;
  //  phrase = "hello";
  strcpy(phrase, "hello world i am a sneaky hacker attempting");
  cout << phrase << endl;
  return 0;

  
	char first_string[MAXIMUM_LENGTH];
	char second_string[MAXIMUM_LENGTH];

	strcpy(first_string, "hello");

	cout << "Enter first string: ";
	//	cin >> first_string;
	//	hello world --->  hello
	cin.getline(first_string,MAXIMUM_LENGTH);
	//	hello world --->  hello world
	cout << "Enter second string: ";
	cin.getline(second_string,MAXIMUM_LENGTH);

	cout << "Before copying the strings were ";
	if (strcmp(first_string,second_string)) 
		cout << "not ";
	cout << "the same." << endl;

	strcpy(first_string,second_string);

	cout << "After copying the strings were ";
	if (strcmp(first_string,second_string)) 
		cout << "not ";
	cout << "the same." << endl;
	
	strcat(first_string,second_string);

	cout << "After concatenating, the first string is: " << first_string << endl;
	
	return 0;
}

