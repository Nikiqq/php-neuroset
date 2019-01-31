#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

double function (double x) {
	double y;
	y = (x-2)*(x-3) - 1;
	return y;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double arr[100], brr[100], h(0.5), b0(5), yrr[100];
	arr[0] = -5;
	int n = 0;
	yrr[0] = function(arr[n]);
	while (arr[n] < b0) {
		brr[n] = arr[n] + h;
		yrr[n+1] = function(brr[n]);

		if(yrr[n]*yrr[n+1] <= 0 ) {
			cout << "Интервал" << arr[n] << ";" << brr[n] <<  "содержит корень" << endl;
			break;
		}
		else {
			n+=1;
		arr[n] = brr[n-1];
		yrr[n] = yrr[n-1];
		}
	}
	
    setlocale(LC_ALL, "Russian");
	//cout << "hello world! " << endl;

	_getch(); // 
	return 0;
}