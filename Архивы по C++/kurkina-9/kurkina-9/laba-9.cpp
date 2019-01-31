#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	const int N = 1000;
    setlocale(LC_ALL, "Russian");
	cout << "hello world! " << endl;
	double xrr[N];
	double yrr[N];
	double dt(0.001);
	double alf = 20;
	xrr[0] = 0.6;
	for(int i = 1; i < N; i++ ) {
		xrr[i] = (1.0/5.0)*alf*xrr[i-1]*(1 - xrr[i-1]); 
	}

	ofstream fout;
	fout.open("laba-9-13.txt");
	for(int i = 0; i < N; i ++ ) {
		fout << i+1 << " " << xrr[i] << endl;
	}

	fout.close();
	_getch(); // 
	return 0;
}