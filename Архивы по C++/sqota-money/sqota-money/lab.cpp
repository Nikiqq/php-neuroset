#include <iostream> 
#include <cstdlib> 
#include <fstream> 
#include<math.h> 
using namespace std; 

int main() 
{ 
setlocale(LC_ALL, "Russian"); 
static double x1 = 0; 
static double x2 = 1; 
static double t1 = 0; 
static double t2 = 1; 
static double h = 0.1; 
static double dt = 0.1; 
static int N1 = 1 + ((x2 - x1) / h); 
static int N2 = 1 + (t2 - t1) / dt; 
cout << N1 << endl << N2 << endl; 
int i, j, n = 0; 
double t, x, a, b, c, ks; 
double **Uj = new double* [N2]; 

for (int count = 0; count < N2; count++) 
	Uj[count]= new double [N1]; 
	double *alph = new double [N1-1]; 
	double *bet = new double [N1-1]; 
	ofstream file("cppstudio.txt", ios_base::out); 

	a = -(7*dt/(pow(h,2))); 
	b = 1 + 2*(7*dt/(pow(h,2))); 
	c = -(7*dt/(pow(h,2))); 
	alph[0] = 0; 
	bet[0] = 0; 

	for (i = 0; i < N1; i++){ 
		t = 0; 
		x = x1 + i * h; 
		Uj[0][i] = x; 
	} 



while (n < N2-1){ 
t = t1 + (n+1) * dt; 
alph[0] = 0; 
bet[0] = 0; 

for (i = 1; i < N1-1; i++){ 
x = x1 + i * h; 
ks = Uj[n][i] + dt*(t*(-140*t+20*pow(x,2))); 
bet[i] = (ks - c* bet[i-1])/(b + c*alph[i-1]); 
alph[i] = -(a/(b+c*alph[i-1])); 
} 

Uj[n+1][N1-1] = (10*pow(t,2)); 
for (i = N1-2; i >= 0; i--){ 
Uj[n+1][i] = alph[i] * Uj[n+1][i+1] + bet[i]; 
} 


n = n+1; 
} 





for (i = N2-1; i >= 0; i--){ 
for (j =0; j < N1 ; j++){ 
file.width(15); 
file << Uj[i][j] ; 
} 
file << endl; 
} 

cout << "прив" << endl; 
file.close(); 
for (int count = 0; count < N2; count++) 
delete []Uj[count]; 
delete []alph; 
delete []bet; 
return 0; 
}