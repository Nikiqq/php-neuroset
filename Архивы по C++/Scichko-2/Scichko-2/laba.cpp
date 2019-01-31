#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;

const double h = 0.1;	
const int N = 10;		

const double dt = 0.001;	
const int M = 1000;		
//const double dt = 0.1;
//const int M = 10;

int main() {
	double u[M + 1][N + 1];		
	double a[N + 1];			
	double b[N + 1];			

								
	for (int j = 0; j < N + 1; j++) {
		u[0][j] = 0;
	}

	
	for (int n = 0; n < M + 1; n++) {

		
		a[0] = 0;
		b[0] = 0;

		
		for (int j = 1; j < N; j++) { //находим коэффициенты 
			double aj = -7 * dt / pow(h, 2);
			double bj = 1 +  2 * 7 * dt / pow(h, 2);
			double cj = aj;
			double Ejn = u[n][j] +  dt  * (20 * ((n + 1) * dt)*pow(h*j, 2) - 140 *pow((dt * (n + 1)), 2)) ;
			a[j] = -aj / (bj + cj * a[j - 1]);
			b[j] = (Ejn - cj * b[j - 1]) / (bj + cj * a[j - 1]);
		}
		u[n + 1][N] = 10* pow((dt * (n + 1)), 2);

		for (int j = N - 1; j >= 0; j--)
			u[n + 1][j] = a[j] * u[n + 1][j + 1] + b[j]; //собственно находим значения
	}

	//вывод
	ofstream fout("0.001.txt");
	for (int n = M; n >= 0; n --) {
		for (int j = 0; j < N + 1; j++) {
			//cout << fixed << setprecision(6) << u[n][j] << " ";
			fout << fixed << setprecision(6) << u[n][j] << " ";
		}
		cout << endl;
		fout << endl;
	}
	fout.close();
	getchar();
	return 0;
}