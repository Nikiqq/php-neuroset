#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>

void Multiplication(float *__restrict__ c, float * a, float * b, int N)
{
#pragma acc parallel loop present(c, a, b)
	for (int n = 0; n < N; n++)
	{
		for (int m = 0; m < N; m++)
		{
			float sum = 0.f;
			for (int k = 0; k < N; k++)
			{
				sum += a[k + n * N] * b[k * N + m ];
			}
			c[m + n * N] = sum;
		}
	}
}
int main()
{
	int i;
	const int N = 4;
	float **Matrix_A = (float**)malloc(N * sizeof(float*));
	for (i = 0; i < N; i++) {
		Matrix_A[i] = (float*)malloc(N * sizeof(float*));
	}
    
	float **Matrix_B = (float**)malloc(N * sizeof(float*));
	for (i = 0; i < N; i++) {
		Matrix_B[i] = (float*)malloc(N * sizeof(float*));
	}
    
	float **Matrix_C = (float**)malloc(N * sizeof(float*));
	for (i = 0; i < N; i++) {
		Matrix_C[i] = (float*)malloc(N * sizeof(float*));
	}
    
	float 
        * a = (float *)malloc(N * N * sizeof(float*)),
		* b = (float *)malloc(N * N * sizeof(float*)),
		* c = (float *)malloc(N * N * sizeof(float*));
        
    srand(time(NULL));
    
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; j++) {
			Matrix_A[i][j] = rand() % 5;
			Matrix_B[i][j] = rand() % 10;
		}
	}
    
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; j++) {
			a[j + i * N] = Matrix_A[i][j];
			b[j + i * N] = Matrix_B[i][j];
		}
	}
	
		
#pragma acc data copyin (a[0:N*N], b[0:N*N]) copyout (c[0:N*N])
	{
		Multiplication(c, a, b, N);
	}

    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%3.0f  ", Matrix_A[i][j]);
		}
		printf("\n");
	}
    
    printf("\n");
    
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%3.0f  ", Matrix_B[i][j]);
		}
		printf("\n");
	}
    
    printf("\n");
    
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			Matrix_C[i][j] = c[j + i * N];
			printf("%3.0f  ", Matrix_C[i][j]);
		}
		printf("\n");
	}
	
	free(a);
	free(b);
	free(c);
	free(Matrix_A);
	free(Matrix_B);
	free(Matrix_C);
}