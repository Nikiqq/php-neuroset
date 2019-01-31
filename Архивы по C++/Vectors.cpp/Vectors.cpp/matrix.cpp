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
	int number(2), N(2), M(3), L(3), K(3); //потом заменить на общее кол-во элементов, а остальные параметры высчитывать
	int **A = sozdanie(number * N, number * M);
	initialize(A, number * N, number * M);
	cout << endl << endl;
	int **B = sozdanie(number * L, number * K);
	initialize(B, number * L, number * K);

	int **C = sozdanie(number * N, number * K);

	cout << endl << "Матрица C: " << endl << endl;

	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < K; j++) 
		{
			int **block_C = sozdanie(number, number);
			for (int C_i = 0; C_i < number; C_i++) 
			{
				for (int C_j = 0; C_j < number; C_j++)
				{
					block_C[C_i][C_j] =  0;
				}

			}
			for (int m = 0; m < M; m++)
			{
				int **block_A = sozdanie(number, number);
				int **block_B = sozdanie(number, number);
				for (int k = 0; k < number; k++) 
				{
					for (int l = 0; l < number; l++) 
					{
						block_A[k][l] = A[i*number+k][m*number+l];
						cout.width(3);
						//cout << block_A[k][l] << "     ";
					}
					//cout << "           ";
					for (int l = 0; l < number; l++) 
					{
						block_B[k][l] = B[m * number + k][j * number + l];
						cout.width(3);
						//cout << block_B[k][l] << "     ";
					}
					//cout << endl;
				}
				//cout << endl << endl;
				block_C = block_proiz(block_A, block_B, block_C, number);
			}
			//cout << "Вызов функции перемножения блоков! " << endl;
			for (int k = 0; k < number; k++) 
			{
				for (int l = 0; l < number; l++) 
				{
					C[i * number + k][j * number + l] = block_C[k][l];
					//cout << C[i * number + k][j * number + l] << "   ";
				}
				//cout << endl;
			}
		}
	}

	for (int i = 0; i < N*number; i++)
	{
		for (int j = 0; j < K*number; j++)
		{
			cout.width(3);
			cout << C[i][j] << "     ";
		}
		cout << endl;
	}

	
	
	_getch(); 
	return 0;
}