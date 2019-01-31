#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	const int N = 18000;
    setlocale(LC_ALL, "Russian");
	cout << "hello world! " << endl;
	double xrr[N];
	double yrr[N];
	double dt(0.001), tay(5), x0(0.8), k1(0.6), k2(0.4);
	xrr[0] = 0;
	yrr[0] = -2;
	for(int i = 1; i < N; i++ ) {
		xrr[i] = xrr[i-1] + dt*((1/tay)*(x0 - xrr[i-1])-k1*xrr[i-1]);
	}

	for(int i = 1; i < N; i++ ) {
		yrr[i] = yrr[i-1] + dt*(-(1/tay)*yrr[i-1] + k1*xrr[i-1] - k2*yrr[i-1]);
	}

	ofstream fout;
	fout.open("laba-1-8.txt");
	for(int i = 0; i < N; i ++ ) {
		fout << i+1 << " " << xrr[i] << " " << yrr[i] << endl;
	}

	fout.close();
	_getch(); // 
	return 0;
}