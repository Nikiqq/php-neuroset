#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int** sozdanie(int n, int m)
{
    int **A;// Создаем матрицу введенной размерности
    A = new int *[n]; // через массив указателей
    for (int i = 0; i < n; i++) {
       A[i] = new int [m];
    }
    return A;
}

void initialize(int** A, int n, int m)// Функция заполнения
{
    srand(time(0));
    for(int i = 0; i < n; i++ )
	{
	    for(int j = 0;  j < m;  j++ )
		{
		    A[i][j] = rand()%11 - 2 ;
			cout.width(3);
		    cout << A[i][j] << "     ";
		}
    cout << endl;
	}
}

int** block_proiz(int** A, int** B, int** C, int razmer)
{
	for (int i = 0; i < razmer; i++) 
	{
		for (int j = 0; j < razmer; j++)
		{
			for (int m = 0; m < razmer; m++)
			{
				C[i][j] += A[i][m] * B[m][j];
			}
		}

	}
	return C;
}

int main()
{
    setlocale(LC_ALL, "Russian");
	int Ax(4), Ay(6), Bx(6), By(6), Ax_number(2), Ay_number(3), Bx_number(3), By_number(3);
	int N = Ax / Ax_number;
	if (Ax % Ax_number > 0) N++;

	int M = Ay / Ay_number;
	if (Ay % Ay_number > 0) M++;

	int K = By / By_number;
	if (By % By_number > 0) K++;

	int **A = sozdanie(Ax, Ay);
	initialize(A, Ax, Ay);
	cout << endl << endl;
	int **B = sozdanie(Bx, By);
	initialize(B, Bx, By);

	int **C = sozdanie(Ax, By);

	cout << endl << "Матрица C: " << endl << endl;

	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < K; j++) 
		{
			int **block_C = sozdanie(Ax_number, By_number);
			for (int C_i = 0; C_i < Ax_number; C_i++) 
			{
				for (int C_j = 0; C_j < By_number; C_j++)
				{
					block_C[C_i][C_j] =  0;
				}

			}
			for (int m = 0; m < M; m++)
			{
				int **block_A = sozdanie(Ax_number, Ay_number);
				int **block_B = sozdanie(Bx_number, By_number);
				for (int k = 0; k < Ax_number; k++) 
				{
					for (int l = 0; l < Ay_number; l++) 
					{
						block_A[k][l] = A[i*Ax_number+k][m*Ay_number+l];
						cout.width(3);
						cout << block_A[k][l] << "     ";
					}
					cout << "           ";
				}
				for (int k = 0; k < Bx_number; k++) 
				{
					for (int l = 0; l < By_number; l++) 
					{
						block_B[k][l] = B[i*Bx_number+k][m*By_number+l];
						cout.width(3);
						cout << block_B[k][l] << "     ";
					}
					cout << "           ";
				}
				cout << endl << endl;
				//block_C = block_proiz(block_A, block_B, block_C, number);
			}
			//cout << "Вызов функции перемножения блоков! " << endl;
			//for (int k = 0; k < number; k++) 
			//{
			//	for (int l = 0; l < number; l++) 
			//	{
			//		C[i * number + k][j * number + l] = block_C[k][l];
			//		//cout << C[i * number + k][j * number + l] << "   ";
			//	}
			//	//cout << endl;
			//}
		}
	}

	/*for (int i = 0; i < N*number; i++)
	{
		for (int j = 0; j < K*number; j++)
		{
			cout.width(3);
			cout << C[i][j] << "     ";
		}
		cout << endl;
	}*/

	
	
	_getch(); 
	return 0;
}
