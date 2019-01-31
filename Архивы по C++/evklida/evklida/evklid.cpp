#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int a(187), b(153);
	int q = 0;
	int U[3] = { a, 1, 0};
	int V[3] = { b, 0, 1};
	int T[3];

	while(V[0] != 0 ) 
	{
		q = U[0]/V[0];
		T[0] = U[0]%V[0];
		T[1] = U[1]-q*V[1];
		T[2] = U[2]-q*V[2];
		for(int i = 0; i < 3; i++ ) {
			U[i] = V[i];
			V[i] = T[i];
		}
	}
		cout << "НОД равен: " << U[0] << endl;
		cout << "x равен: " << U[1] << endl;
		cout << "y равен: " << U[2] << endl;
	_getch(); // 
	return 0;
}