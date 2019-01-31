#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
	const int N = 19000;
    setlocale(LC_ALL, "Russian");
	cout << "hello world! " << endl;
	double xrr[N];
	double yrr[N];
	double dt(0.001);
	/*xrr[0] = -3;
	yrr[0] = 1;*/
	/*for(int i = 1; i < N; i++ ) {
		xrr[i] = xrr[i-1] + dt*((xrr[i-1] + 2)*(xrr[i-1] + 2)+ 2*alf -3);
	}

	for(int i = 1; i < N; i++ ) {
		yrr[i] = yrr[i-1] + dt*(alf*xrr[i-1] - yrr[i-1]);
	}*/
	double alf = 1;
	int i = 0;
	while(alf <= 20) {
		yrr[i] = (alf-5)/alf;
		xrr[i] = alf;
		i++;
		alf+=dt;
	}


	ofstream fout;
	fout.open("laba-7-24.txt");
	for(int i = 0; i < N; i ++ ) {
		fout << i+1 << " " << xrr[i] << " " << yrr[i] << endl;
	}

	fout.close();
	_getch(); // 
	return 0;
}