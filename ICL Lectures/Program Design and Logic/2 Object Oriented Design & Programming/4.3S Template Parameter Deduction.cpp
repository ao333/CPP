template<typename T, typename U>
U foo(T t) { };

template<typename T, typename U = int> //default type needs c++11
void bar(T t = 0, U u = 0) { };

template<typename T>
char f(T) { return 'a'; } //#1

char f(int x) { return 'b'; }  //#2

int main() {

	//int x = foo(5); // U cannot be deduced; T is int
	bar(1);           // bar<int, int>(1, 0)
	//bar();          // T cannot be deduced

	/* Empty template argument list refers to a specialisation of a function
	 * template */

	char c = f<>(550); //uses function template #1
	c = f(550);        //uses function #2

	return 0;
}
