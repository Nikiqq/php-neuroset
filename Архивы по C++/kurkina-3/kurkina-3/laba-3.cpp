#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	const int N = 20000;
    setlocale(LC_ALL, "Russian");
	cout << "hello world! " << endl;
	double xrr[N];
	double yrr[N];
	double dt(0.001), tay(5), x0(0.8), k1(0.6), k2(0.4);
	xrr[0] = 10;
	yrr[0] = -2.9;
	for(int i = 1; i < N; i++ ) {
		xrr[i]  = (xrr[i-1] )/(1+4*dt);
	}

	for(int i = 1; i < N; i++ ) {
		yrr[i] = yrr[i-1] + dt*(yrr[i-1]+3);
	}

	ofstream fout;
	fout.open("laba-3-8.txt");
	for(int i = 0; i < N; i ++ ) {
		fout << i+1 << " " << xrr[i] << " " << yrr[i] << endl;
	}

	fout.close();
	_getch(); // 
	return 0;
}