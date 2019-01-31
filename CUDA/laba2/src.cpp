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

int** block_proiz(int** A, int** B, int** C, int x_razmer, int y_razmer, int m_razmer)
{
	for (int i = 0; i < x_razmer; i++) 
	{
		for (int j = 0; j < y_razmer; j++)
		{
			for (int m = 0; m < m_razmer; m++)
			{
				C[i][j] += A[i][m] * B[m][j];
			}
			//cout << "C["<< i << "][" << j <<"] " << C[i][j] << "   ";
			
		}
		//cout << endl << endl;
	}
	return C;
}

int main()
{
    setlocale(LC_ALL, "Russian");
	int Ax(3), Ay(4), Bx(4), By(3), Ax_number(2), Ay_number(3), Bx_number(3), By_number(3);
	int N = Ax / Ax_number;
	if (Ax % Ax_number > 0) N++;
	int Ax_ostatok = Ax % Ax_number;

	int M = Ay / Ay_number;
	if (Ay % Ay_number > 0) M++;
	int Ay_ostatok = Ay % Ay_number;

	int K = By / By_number;
	if (By % By_number > 0) K++;
	int By_ostatok = By % By_number;

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
						if ((i*Ax_number+k+1 > Ax) || (m*Ay_number+l+1 > Ay)) {
							block_A[k][l] = 0;
						}
						else {
							block_A[k][l] = A[i*Ax_number+k][m*Ay_number+l];
						}
						//cout.width(3);
						//cout << block_A[k][l] << "   ";
					}
					//cout << endl;
				}
				//cout << endl << endl;
				for (int k = 0; k < Bx_number; k++) 
				{
					for (int l = 0; l < By_number; l++) 
					{
						if((m*Bx_number+k+1 > Bx) || (j*By_number+l+1 > By)) {
							block_B[k][l] = 0;
						}
						else {
							block_B[k][l] = B[m*Bx_number+k][j*By_number+l];
						}
						//cout.width(3);
						//cout << block_B[k][l] << "   ";
					}
					//cout << endl;
				}
				//cout << endl << endl;
				block_C = block_proiz(block_A, block_B, block_C, Ax_number, By_number, Ay_number );
			}
			//cout << "Вызов функции перемножения блоков! " << endl;
			for (int k = 0; k < Ax_number; k++) 
			{
				for (int l = 0; l < By_number; l++) 
				{
					if((i * Ax_number + k < Ax) && (j * By_number + l < By)) {
						C[i * Ax_number + k][j * By_number + l] = block_C[k][l];
					}
				}
			}
		}
	}

	for (int i = 0; i < Ax; i++)
	{
		for (int j = 0; j < By; j++)
		{
			cout.width(3);
			cout << C[i][j] << "     ";
		}
		cout << endl;
	}

	
	
	return 0;
}
