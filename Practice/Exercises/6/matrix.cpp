#include<iostream>
using namespace std;

const int M = 2;
const int N = 2;
const int R = 2;

void input_a_matrix(int a[M][N]){
  for (int row=0; row<M; row++){
    cout << "Type in " << M << " values for row " << row+1 << " separated by spaces: ";
    for (int column=0; column<N; column++)
      cin >> a[row][column];
  }
}

void input_b_matrix(int b[N][R]){
  for (int row=0; row<N; row++){
    cout << "Type in " << N << " values for row " << row+1 << " separated by spaces: ";
    for (int column=0; column<R; column++)
      cin >> b[row][column];
  }
}

void display_a_matrix(int a[][N], int a_row){
    for (int row=0; row<a_row; row++){
      cout << endl;
      for (int column=0; column<N; column++)
        cout << a[row][column] << " ";
    }
    cout << endl;
}

void display_x_matrix(int x[][R], int x_row){
    for (int row=0; row<x_row; row++){
      cout << endl;
      for (int column=0; column<R; column++)
        cout << x[row][column] << " ";
    }
    cout << endl;
}

// A r0c0 * B r0c0 + A r0c1 * B r1c0 = C r0c0
// A r0c0 * B r0c1 + A r0c1 * B r1c1 = C r0c1
// A r1c0 * B r0c0 + A r1c1 * B r1c0 = C r1c0
// A r1c0 * B r0c1 + A r1c0 * B r1c1 = C r1c1

void matrix_mult(int a[M][N], int b[N][R], int c[M][R]){
  int sum=0;
  for (int row=0; row<M; row++)
    for (int col=0; col<R; col++)
      for (int count=0; count<N; count++)
        c[row][col] += a[row][count] * b[count][col];
}

int main(){
	int a[M][N] = {0};
	int b[N][R] = {0};
	int c[M][R] = {0};

	cout << "INPUT FIRST (" << M << "x" << N << ") MATRIX:\n";
	input_a_matrix(a);
	cout << "INPUT SECOND (" << N << "x" << R << ") MATRIX:\n";
	input_b_matrix(b);

	matrix_mult(a, b, c);
	cout << endl;

	display_a_matrix(a,M);
	cout << "\nTIMES\n";
	display_x_matrix(b,N);
	cout << "EQUALS\n";
	display_x_matrix(c,M);

	return 0;
}
