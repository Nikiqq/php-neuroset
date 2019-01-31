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
	//cout << i << endl;
	int n = i;
	//cout << n << endl;

	int *arr = new int[n];
	while( a < 0) 
	{
		a+=p;
	}
    arr[0] = a;
    //cout << arr[0] << endl;
    for(int i = 1; i < n; i++ ) {
        arr[i] = (arr[i-1]* arr[i-1])%p;
        //cout << arr[i] << endl;
    }
    //cout << arr[2] << endl;
    //int j = n;
    //cout << "sdsad" << x2[6] << endl;
    long long unsigned int proizv = 1;
    for(int j = 0; j < n; j++) {
        if (x2[j] > 0){
            proizv*= x2[j]* arr[j];
            //cout << proizv << endl;
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
	if(a < b) {
		int temp = a;
		a = b;
		b = a;
	}
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
	int m(10), hm;
	hm = m;
	long long int p, b, q, a, x, y, k, r, s, w, u1, u2, v;
	p = 43441;
	b = 240;
	q = (p - 1)/b;
	a = 0;
	const int N = 10;
	/*int arr [N][N] = {{ 0 }};
	cout << arr[8][9] ;*/
	//cout << function(b,1,q) << endl;
	for (int i = 2; i < p-1; i++ )
	{
		if(function(i, function(b, 1, q),p) != 1) 
		{
			a = i;
			break;
		}
		else 
		{
			
		}

	}
	cout << "p = " << p << " q = " << q << " a = " << a << endl;
	x = 1 + rand()%q-1;
	y = function(a, x, p);

	k = 1 + rand()%q-1;

	cout << "x = " << x << " y = " << y << " k = " << k << endl;
	r = function(function(a, k, p), 1, q);
	s = function(function(evklid(q, k,2), 1, q)*function((hm+x*r), 1 , q), 1, q);

	cout << "Получена подпись: <" << r << ", " << s << ">" << endl;

	w = function(evklid(q, s, 2), 1, q);
	u1 = function((hm*w), 1, q);
	u2 = function((r*w), 1, q);
	v = function(function((function(a,u1,p))*(function(y,u2,p)), 1 , p), 1, q);

	cout << "v = " << v;
	_getch(); // 
	return 0;
}