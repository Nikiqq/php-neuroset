
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int a, a1, x, stepen, dl, d;

	cout << "Введите число: " << endl;
	cin >> a;
	cout << "Введите степень: " << endl;
	cin >> x;
	cout << "Введите значение для mod: " << endl;
	cin >> d;
	stepen = x;
	a1 = a;
	int i = 0;
	while (stepen > 0) {
		stepen /= 2;
		i++;
		dl = i;
	}
	i = 0;
	stepen = x;
	int *dv = new int[dl];
	int *arrayPow = new int[dl];
	while (stepen > 0) {
		dv[i] = stepen % 2;
		stepen /= 2;
		i++;
	}
	cout << endl << "Шифруемое число в двоичной системе счисления " << endl;
	for (int j = i - 1; j >= 0; j--) {
		cout << dv[j];
	}
	cout << endl;
	
	cout << endl <<"Количество символов в двоичной системе счисления " << dl << endl;
	for (i = 0; i < dl; i++) {
		cout << setw(4) << 'a' << i;
	}
	cout << endl;
	arrayPow[0] = a;
	for (i = 1; i < dl; i++) {
		arrayPow[i] = (arrayPow[i - 1]) * (arrayPow[i - 1]);
		arrayPow[i] %= d;
		a1 = a;
	}
	for (i = 0; i < dl; i++) {
		cout << setw(5) << arrayPow[i];

	}
	cout << endl;
	long long unsigned int rez = 1;
	for (int j = dl - 1; j >= 0; j--) {
		if (dv[j] > 0)
			rez *= arrayPow[j];

	}
	
	cout << endl <<"Результат перемножения полученных степеней: " << rez << endl;
	rez %= d;
	cout << endl <<"Зашифрованное значение: " << rez << endl;
	delete[] arrayPow;
	delete[] dv;
	_getch(); 
    return 0;
}


