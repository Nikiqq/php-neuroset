#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int function(int a, int x, int p) {
	int i(0);
	int *x2 = new int[30];
    while(x >= 1)
    {
        x2[i] = x%2;
        x /= 2;
		i++;
	}
	int n = i;
	int *arr = new int[n];
	while( a < 0) 
	{
		a+=p;
	}
    arr[0] = a;
    for(int i = 1; i < n; i++ ) {
        arr[i] = (arr[i-1]* arr[i-1])%p;
    }
    long long unsigned int proizv = 1;
    for(int j = 0; j < n; j++) {
        if (x2[j] > 0){
            proizv*= x2[j]* arr[j];
		}
	}
	int ostatok = proizv%p;
	return ostatok;
}
bool prostoe(int a)
{
	bool pr = true;
	for (int i=2; i < a; i++)
	{
		if (a%i==0)
		{
			pr=false;
		}
	}
return pr;
}
int evklid(int a, int b, int num) 
{
	int q = 0;
	int U[3] = { a, 1, 0};
	int V[3] = { b, 0, 1};
	int T[3];

	while(V[0] != 0 ) 
	{
		q = U[0]/V[0];
		T[0] = U[0]%V[0];
		T[1] = U[1]-q*V[1];
		T[2] = U[2]-q*V[2];
		for(int i = 0; i < 3; i++ ) {
			U[i] = V[i];
			V[i] = T[i];
		}
	}
	return U[num];
}

int main()
{
	setlocale(LC_ALL, "Russian");
	unsigned long long int  m = 80;
	cout << "Исходное сообщение m = " << m << endl << endl;
	unsigned long long int P(4), Q(4), N, F, d(4) , C , e, m1(0);
	srand( time(NULL) );
	while(!prostoe(P)) 
	{
		P = 20 + rand()%30;
	}
	while((!prostoe(Q)) + (Q == P)) 
	{
		Q = 20 + rand()%30;
	}

	N = P*Q;
	F = (P-1)*(Q-1);
	while(evklid(d, F, 0) != 1) 
	{
		d = 0 + rand()%100;
	}

	C = function(evklid(F, d, 2), 1, F);
	e = function(m,d,N);
	m1 = function(e, C, N);
	cout << "P = " << P << "  Q = " << Q << endl << "N = " << N << endl << "F = " << F << endl << "d = " << d << endl << "C = " << C << endl << "e = " << e << endl << "m' = " << m1 << endl; 
	_getch(); // 
	return 0;
}

