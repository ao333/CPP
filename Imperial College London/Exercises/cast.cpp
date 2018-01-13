#include <iostream>
#include <limits>
#include <cmath>
//#include <atomic>

using namespace std;

int main() 
{

  float x = 5.6;
  cout << static_cast<long double>(x) << endl;
  
  cout << "sizeof(char) = " << sizeof(char) << endl;
  cout << "sizeof(char16_t) = " << sizeof(char16_t) << endl;
  cout << "sizeof(short) = " << sizeof(short) << endl;
  cout << "sizeof(int) = " << sizeof(int) << endl;
  cout << "sizeof(long) = " << sizeof(long) << endl;
  cout << "sizeof(long long) = " << sizeof(long long) << endl;
  
  cout << "sizeof(float) = " << sizeof(float) << endl;
  cout << "sizeof(double) = " << sizeof(double) << endl;
  cout << "sizeof(long double) = " << sizeof(long double) << endl;
  cout << "sizeof(unsigned char) = " << sizeof(unsigned char) << endl;
  cout << "short goes from " << numeric_limits<short>::min() << " to " << numeric_limits<short>::max() << endl;
  cout << "int goes from " << numeric_limits<int>::min() << " to " << numeric_limits<int>::max() << endl;
  cout << "unsigned int goes from " << numeric_limits<unsigned int>::min() << " to " << numeric_limits<unsigned int>::max() << endl;
  cout << "float min " << numeric_limits<float>::min() << " float max " << numeric_limits<float>::max() << endl;
  cout << "double min " << numeric_limits<double>::min() << " double max " << numeric_limits<double>::max() << endl;
  cout << "float epsilon: " << numeric_limits<float>::epsilon() << endl;
  cout << "double epsilon: " << numeric_limits<double>::epsilon() << endl;
  
  return 0;

  
  int a,b;
  double c;
  unsigned char d;

  cout << "-7/2 = " << -7/2 << endl;

  cout << "-7.0/2 = " << -7.0/2 << endl << endl;
  cout << "-7/2.0 = " << -7/2.0 << endl << endl;

  a = -7;
  b = 2;     

  cout << "a/b = " << a << "/" << b << " = " << a/b << endl << endl;
 
  // C++ style (new) cast 
  cout << "static_cast<double>(a)/b = static_cast<double>(" << a << ")/" << b << " = ";
  cout << static_cast<double>(a)/b << endl;

  // C++ style (old) cast 
  cout << "double(a)/b = double(" << a << ")/" << b << " = ";
  cout << double(a)/b << endl;
  
  // C style cast
  cout << "(double) a/b = (double) " << a << "/" << b << " = ";
  cout << (double) a/b << endl << endl;

  // cast's don't always make sense, be careful
  cout << "(unsigned int) " << a << " = " << (unsigned int) a << endl << endl;

  c = (a-b)*(a-b) + 0.25;

  cout << "c = " << c << endl;
  cout << "int(c) = (int) c = " << int(c) << endl;

  d = char(c);

  cout << "d = char(c) = (char) c = " << d << endl;

  return 0;
}



