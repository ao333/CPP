#include <iostream> 
	
	using namespace std; 
	
	int main() 
	{ 
	  int year_now, age_now, another_year, another_age, month_now, month_born, month_this   ; 
	 
		cout << "Enter the current year then press RETURN.\n"; 
		cin >> year_now;

		cout << "Enter the current month.\n";
		cin >> month_now  ;

		cout << "Enter your current age in years.\n"; 
		cin >> age_now;

		cout << "Enter the month in which you were born.\n";
		cin >> month_born ;
		
		cout << "Enter the year for which you wish to know your age.\n";
		cin >> another_year;

		cout << "Enter the month in this year\n";
		cin >> month_this ;
	 
		another_age = another_year - (year_now - age_now); 
	 
		if (another_age >= 0) {
		  cout << "Your age in " << month_this << "/" << another_year << ": "
		       << another_year - year_now + age_now << " years and "
		       << month_this - month_born << " month \n";}
		if (another_age > 150) {
			cout << "Sorry, but you'll probably be dead by " << another_year << "!";}
		else { 
			cout << "You weren't even born in ";
			cout << another_year << "!\n";}
	
		return 0; 
	}
