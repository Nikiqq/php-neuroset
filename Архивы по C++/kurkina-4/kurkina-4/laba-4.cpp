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
	double xrr_pol[N];
	double yrr_pol[N];
	double dt(0.01), alf(2.2), sigma(1.5), c(2.8), gamma(1);
	xrr[0] = 3;
	yrr[0] = 5;
	
	for(int i = 1; i < N; i++ ) {
		xrr_pol[i]  = xrr[i-1] + 0.5*dt*(alf * xrr[i-1] - sigma * xrr[i - 1] * yrr[i - 1]);
		yrr_pol[i] = yrr[i-1] + 0.5*dt*(- c * yrr[i-1] + gamma * xrr[i - 1] * yrr[i - 1]);
		xrr[i]  = xrr[i-1] + dt*(alf * xrr_pol[i] - sigma * xrr_pol[i] * yrr_pol[i]);
		yrr[i] = yrr[i-1] + dt*(-c * yrr_pol[i] + gamma * xrr_pol[i] * yrr_pol[i]);
	}

	ofstream fout;
	fout.open("laba-4-runge.txt");
	for(int i = 0; i < N; i ++ ) {
		fout << i+1 << " " << xrr[i] << " " << yrr[i] << endl;
	}

	fout.close();
	_getch(); // 
	return 0;
}