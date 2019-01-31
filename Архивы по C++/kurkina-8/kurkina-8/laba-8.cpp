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
	double dt(0.001);
	double alf = 0;
	xrr[0] = 0.5;
	yrr[0] = 0.5;
	for(int i = 1; i < N; i++ ) {
		xrr[i] = xrr[i-1] + dt*(0.4*alf*xrr[i-1] - yrr[i-1] - 0.6*xrr[i-1]*(xrr[i-1]*xrr[i-1] + yrr[i-1]*yrr[i-1]));
		yrr[i] = yrr[i-1] + dt*(xrr[i-1] + 0.4*alf*yrr[i-1] - 0.6*yrr[i-1]*(xrr[i-1]*xrr[i-1] + yrr[i-1]*yrr[i-1]));
			 
	}

	ofstream fout;
	fout.open("laba-8-8.txt");
	for(int i = 0; i < N; i ++ ) {
		fout << i+1 << " " << xrr[i] << " " << yrr[i] << endl;
	}

	fout.close();
	_getch(); // 
	return 0;
}