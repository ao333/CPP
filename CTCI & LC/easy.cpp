c#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

void print(istream& in, ostream& cout){
  char ch;
  char line[512];
  while(in){
    in.get(ch);
    cout.put(ch);
  }
  while(in){
    in.getline(line,512);
    ofstream out("output.txt");
    out<<line;
    out.close();
  }
}

int main () {
  ifstream in("test.txt");
  print(in,cout);
  cout<<endl;
  in.close();


  const char s1[512]={"Please split, this, sentence"};
  const char sn[512]={"43"};

  const char*c=strchr(s1,'e');
  cout<<"strchr: "<<c<<endl;

  const char*cr=strrchr(s1,'e');
  cout<<"strrchr: "<<cr<<endl;

  const char*sr=strstr(s1,"this");
  cout<<"strstr: "<<sr<<endl;

 // int c = cin.peek();  // peek character
 //
 //  if ( c == EOF ) return 1;

  int num = atoi(sn);
  cout<<num*2<<endl;

  char s2[strlen(s1)];
  strncpy(s2,s1+7,strlen(s1)-7);
  cout<<s2;

  char *p = strtok(s2,", ");
  int i=0;
  while(p!=NULL){
    cout<<p<<endl;
    p=strtok(NULL,", ");
  }

  return 0;
}



// string OddNumber (int k) {
//   int i = 0, k = 10;
//   i = (i % 2 == 0? i + 1: i);
//   while (i <= k){
//     cout << i << endl;
//     i = i+2;
//   }
// }
//
// string findNumber(vector<int> arr, int k) {
//   if (find(arr.begin(), arr.end(), k) != arr.end())
//     return "YES";
//   else
//     return "NO";
// }
//
// string runLengthEncode(string input) {
//   string output;
// 	for (int i = 0; input[i]; i++) {
// 		int count = 1;
// 		while (input[i] == input[i + 1])
// 			count++, i++;
// 		output += to_string(count) + input[i];
// 	}
// 	return output;
// }
