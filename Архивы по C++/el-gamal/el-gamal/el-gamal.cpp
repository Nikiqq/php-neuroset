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
int main()
{
	setlocale(LC_ALL, "Russian");
	int m = 10;
	int q = 53;
	int p = 2*q + 1;
	// Подбор g простое и (g^q)modp!= 1
	int g; 
	for(g = 1; g < p-1; g++)
	{
		if((prostoe(g) == 1) && (function(g,q,p)!=1))
		{
			cout << "Выбранное число g: " << g << endl<< endl;
			break;
		}
		//cout << function(g,q,p);
	}
	srand( time(NULL) );
	int Cb = 1+ rand()%(p-2);
	//Cb= 13;
	cout << "Исходное сообщение m = " << m << "\nСгенерированное Cb= " << Cb << endl; 
	int db = function(g,Cb,p);
	cout << "db= " << db << endl;
	int k = 1 + rand()%(p-3);
	//k = 7;
	cout << "Сгенерированное k= " << k << endl;
	int r = function(g,k,p);
	cout << "r= " << r << endl;
	int e = function(m*function(db,k,p), 1, p);
	cout << "e= " << e << endl;
	cout << "Абонент А передает пару чисел B (" << r << ";"  << e << ")" << endl;
	int mb = function(e*function(r,p-1-Cb,p), 1, p);
	cout << "Абонент B получил исходное сообщение m' = " <<  mb << endl;
	_getch(); // 
	return 0;
}