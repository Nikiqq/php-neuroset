#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int a(3), x(90), p(5), i(0) ;
	int vi = x; // ���������� ��� ������ �� �����

    int *x2 = new int[30]; // ������� ���������� ������ ���
    while(x >= 1) // �������� � �������� ������� ����������
    {
        x2[i] = x%2;
        x /= 2;
		i++;
	}
	int n = i; // ���������� ���������� ����

	int *arr = new int[n]; // ������ ��������
    arr[0] = a; // 1 �������
    for(int i = 1; i < n; i++ ) {
        arr[i] = (arr[i-1]* arr[i-1])%p; 
    }
    int proizv = 1;
    for(int j = 0; j < n; j++) {
        if (x2[j] > 0){
            proizv*= x2[j]* arr[j];
		}
	}
	cout << "������� �� ������� " << a << "^(" << vi << ")mod" << p << " �����: " << proizv%p << endl;
	delete [] x2;
	delete [] arr;
	_getch(); // 
	return 0;
}
