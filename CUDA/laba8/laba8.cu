#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>

using namespace std;

const double step_t = 0.1;
const double step_xyz = 0.1;
const int Nt = 10;
const int rasmer = 3;
const int Nxyz = 10;
const double sigma = 2;


__global__ void calculate_x(double * in, double * out, int n, double step_t, double step_xyz, double sigma, int Nxyz)
{

	
	double * a = (double *)malloc(Nxyz * sizeof(double));
	double * b = (double *)malloc(Nxyz * sizeof(double));
	a[0] = 0;
	b[0] = sin((n * step_t) / 8);
		
	for (int j = 1; j < Nxyz - 1; j++) {
		a[j] = -(-sigma * step_t / step_xyz) / ((1 + 2 * sigma * step_t / step_xyz) + (-sigma * step_t / step_xyz) * a[j - 1]);
		b[j] = (in[threadIdx.y + threadIdx.y * threadIdx.x + threadIdx.y * threadIdx.x * (j - 1)] - (-sigma * step_t / step_xyz) * b[j - 1]) / ((1 + 2 * sigma * step_t / step_xyz) + (-sigma * step_t / step_xyz) * a[j - 1]);
	}
	out[threadIdx.y + threadIdx.y * threadIdx.x + threadIdx.y * threadIdx.x * (Nxyz - 1)] = sin((n * step_t) / 4);
	for (int j = Nxyz - 2; j > 0; j--) {
		out[threadIdx.y + threadIdx.y * threadIdx.x + threadIdx.y * threadIdx.x * j] = a[j] * out[threadIdx.y + threadIdx.y * threadIdx.x + threadIdx.y * threadIdx.x * (j + 1)] + b[j];
	}
	free(a);
	free(b);
	__syncthreads();
}

__global__ void calculate_y(double * in, double * out, int n, double step_t, double step_xyz, double sigma, int Nxyz)
{


	double * a = (double *)malloc(Nxyz * sizeof(double));
	double * b = (double *)malloc(Nxyz * sizeof(double));
	a[0] = 0;
	b[0] = sin((n * step_t) / 8);

	for (int k = 1; k < Nxyz - 1; k++) {
		a[k] = -(-sigma * step_t / step_xyz) / ((1 + 2 * sigma * step_t / step_xyz) + (-sigma * step_t / step_xyz) * a[k - 1]);
		b[k] = (in[threadIdx.y + threadIdx.y * (k - 1) + threadIdx.y * (k - 1) * threadIdx.x] - (-sigma * step_t / step_xyz) * b[k - 1]) / ((1 + 2 * sigma * step_t / step_xyz) + (-sigma * step_t / step_xyz) * a[k - 1]);
	}
	out[threadIdx.y + threadIdx.y * (Nxyz - 1) + threadIdx.y  * (Nxyz - 1) * threadIdx.x] = sin((n * step_t) / 4);
	for (int k = Nxyz - 2; k > 0; k--) {
		out[threadIdx.y + threadIdx.y * k + threadIdx.y * k * threadIdx.x ] = a[k] * out[threadIdx.y + threadIdx.y * (k + 1) + threadIdx.y * (k + 1) * threadIdx.x] + b[k];
	}
	free(a);
	free(b);
	__syncthreads();
}

__global__ void calculate_z(double * in, double * out, int n, double step_t, double step_xyz, double sigma, int Nxyz)
{


	double * a = (double *)malloc(Nxyz * sizeof(double));
	double * b = (double *)malloc(Nxyz * sizeof(double));
	a[0] = 0;
	b[0] = sin((n * step_t) / 8);

	for (int m = 1; m < Nxyz - 1; m++) {
		a[m] = -(-sigma * step_t / step_xyz) / ((1 + 2 * sigma * step_t / step_xyz) + (-sigma * step_t / step_xyz) * a[m - 1]);
		b[m] = (in[(m - 1) + (m - 1) * threadIdx.y + (m - 1) * threadIdx.y * threadIdx.x ] - (-sigma * step_t / step_xyz) * b[m - 1]) / ((1 + 2 * sigma * step_t / step_xyz) + (-sigma * step_t / step_xyz) * a[m - 1]);
	}
	out[(Nxyz - 1) + (Nxyz - 1) * threadIdx.y + (Nxyz - 1) * threadIdx.y * threadIdx.x] = sin((n * step_t) / 4);
	for (int m = Nxyz - 2; m > 0; m--) {
		out[m + m * threadIdx.y + m * threadIdx.y * threadIdx.x] = a[m] * out[(m + 1) + (m + 1) * threadIdx.y + (m + 1) * threadIdx.y * threadIdx.x] + b[m];
	}
	free(a);
	free(b);
	__syncthreads();
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "hello world!" << endl;
	double U[rasmer * Nt + 1][Nxyz][Nxyz][Nxyz];

	
	for (int j = 0; j < Nxyz; j++) {
		for (int k = 0; k < Nxyz; k++) {
			for (int m = 0; m < Nxyz; m++) {
				U[0][j][k][m] = 0;
			}
		}
	}
    
    double *row_in = new double [(Nxyz-2) * (Nxyz-2) * (Nxyz-2)];
	double *row_out = new double [(Nxyz-2) * (Nxyz-2) * (Nxyz-2)];

	double *row_in_gpu, *row_out_gpu;

	cudaMalloc((void **)&row_in_gpu, sizeof(double) * (Nxyz-2) * (Nxyz-2) * (Nxyz-2));
	cudaMalloc((void **)&row_out_gpu, sizeof(double) * (Nxyz-2) * (Nxyz-2) * (Nxyz-2));
	
	for (int n = 1; n <= rasmer; n ++) {
        for (int j = 1; j < Nxyz - 1; j++) {
			for (int k = 1; k < Nxyz - 1; k++) {
                for (int m = 1; m < Nxyz - 1; m++ ) {
					row_in[(m - 1) + (m - 1)*(k - 1) + (m - 1)*(k - 1)*(j - 1)] = U[n - 1][j][k][m];
                }
            }
        }

		cudaMemcpy(row_in_gpu, row_in, sizeof(double) * (Nxyz - 2) * (Nxyz - 2) * (Nxyz - 2), cudaMemcpyHostToDevice);

		dim3 gridDim(1);
		dim3 blockDim(Nxyz - 2, Nxyz - 2);

		calculate_x < << gridDim, blockDim >> >(row_in_gpu, row_out_gpu, n, step_t, step_xyz, sigma, Nxyz);

		cudaMemcpy(row_out, row_out_gpu, sizeof(double) * (Nxyz - 2) * (Nxyz - 2) * (Nxyz - 2), cudaMemcpyDeviceToHost);

		//посчитали x
        
		cudaMemcpy(row_in_gpu, row_out, sizeof(double) * (Nxyz - 2) * (Nxyz - 2) * (Nxyz - 2), cudaMemcpyHostToDevice);


		calculate_y < << gridDim, blockDim >> >(row_in_gpu, row_out_gpu, n, step_t, step_xyz, sigma, Nxyz);

		cudaMemcpy(row_out, row_out_gpu, sizeof(double) * (Nxyz - 2) * (Nxyz - 2) * (Nxyz - 2), cudaMemcpyDeviceToHost);
		
		//посчитали y

		cudaMemcpy(row_in_gpu, row_out, sizeof(double) * (Nxyz - 2) * (Nxyz - 2) * (Nxyz - 2), cudaMemcpyHostToDevice);


		calculate_z < << gridDim, blockDim >> >(row_in_gpu, row_out_gpu, n, step_t, step_xyz, sigma, Nxyz);

		cudaMemcpy(row_out, row_out_gpu, sizeof(double) * (Nxyz - 2) * (Nxyz - 2) * (Nxyz - 2), cudaMemcpyDeviceToHost);

		//посчитали z

		for (int j = 1; j < Nxyz - 1; j++) {
			for (int k = 1; k < Nxyz - 1; k++) {
				for (int m = 1; m < Nxyz - 1; m++) {
					U[n][j][k][m] = row_out[(m - 1) + (m - 1)*(k - 1) + (m - 1)*(k - 1)*(j - 1)];
				}
			}
		}
		cout << U[n][Nxyz - 2][Nxyz - 2][1];
	}
	
	_getch();
	return 0;
}