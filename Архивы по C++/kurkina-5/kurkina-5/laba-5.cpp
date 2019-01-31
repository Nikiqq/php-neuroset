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
	xrr[0] = -7;
	yrr[0] = -5;
	for(int i = 1; i < N; i++ ) {
		xrr[i] = (((-2)*yrr[i-1] + 8 )*dt + xrr[i-1])/(1+2*dt); 
		yrr[i] = ((3*xrr[i-1] + 12)*dt + yrr[i-1])/(1+3*dt); 
	}

	ofstream fout;
	fout.open("laba-5-8.txt");
	for(int i = 0; i < N; i ++ ) {
		fout << i+1 << " " << xrr[i] << " " << yrr[i] << endl;
	}

	fout.close();
	_getch(); // 
	return 0;
}