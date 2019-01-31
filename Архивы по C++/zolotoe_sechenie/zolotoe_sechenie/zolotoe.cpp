#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;
 
 
// Рассматриваемая нами функция
double function(double x) {
	return x + 1/log(x);
	//return x*x*x*x + 8*x*x*x - 6*x*x - 72*x;
}
 
int main() {
	setlocale(LC_ALL, "Russian");
	int width = 11;
	double a, b; // Концы отрезка
	double accuracy; // Точность, с которой мы находим локальный максимум
	double x1, x2; // Точки, делящие текущий отрезок в отношении золотого сечения
	double goldenRatio = 1.618033; // "Золотое" число
	cin >> a >> b >> accuracy;
	cout << "-------------------------------------------------------------------------------" << endl;
	x1 = b - (b - a) / goldenRatio; 
	x2 = a + (b - a) / goldenRatio;
	cout << "       e           a          b         x1         x2       f(x1)       f(x2)" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout.width(width);	cout << b-a; cout.width(width);	cout << a;	cout.width(width);	cout << b;	cout.width(width);	cout << x1;	cout.width(width);	cout << x2;	cout.width(width);	cout << function(x1);	cout.width(width);	cout << function(x2) << endl;
	while (abs(b - a) > accuracy) {
		   
	       if (function(x1) >= function(x2)) { // Условие для поиска минимума
	           a = x1; 
		       x1 = x2;
			   x2 = x2 = a + (b - a) / goldenRatio;
		   }
	       else {
			   b = x2;
			   x2 = x1;
			   x1 = b - (b - a) / goldenRatio;
		   }
	cout.width(width);
	cout << b-a;
	cout.width(width);
	cout << a;
	cout.width(width);
	cout << b;
	cout.width(width);
	cout << x1;
	cout.width(width);
	cout << x2;
	cout.width(width);
	cout << function(x1);
	cout.width(width);
	cout << function(x2) << endl;
	
	}
	cout << endl << " Минимум:";
	cout << endl << " x = " << (a + b) / 2 << "\n y = " << function((a + b) / 2) <<  endl;
	
	
	_getch();
	return 0;
}