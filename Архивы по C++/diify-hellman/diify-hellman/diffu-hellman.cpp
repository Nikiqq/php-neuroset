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
	int q = 11;
	int p = 2*q + 1;
	//p = 7;
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
	g = 3;
	// генерируем
	int Xa, Xb;
	srand( time(NULL) );
	Xa =  1 + rand()%10;
	cout << "Сгенерированное число Xa: " << Xa << endl<< endl;
	Xb =  1 + rand()%10;
	cout << "Сгенерированное число Xb: " << Xb << endl<< endl;
	//Xa = 3;
	//Xb = 6;
	//cout << g << " " <<  p << " " << Xa << " " << Xb << endl;
	int Ya = function(g,Xa,p);
	cout << "Ya = " << Ya << endl; 
	int Yb = function(g,Xb,p);
	cout << "Yb = " << Yb << endl;
	int Zab = function(Yb,Xa,p);
	int Zba = function(Ya,Xb,p);
	cout << "Zab = " << Zab << "    "  << "Zba = " << Zba ;
	
	_getch(); // 
	return 0;
}