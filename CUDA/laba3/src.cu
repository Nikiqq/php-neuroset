#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

#define RASMER 2

__host__ int** sozdanie(int n, int m)
{
    int **A;
    A = new int *[n]; 
    for (int i = 0; i < n; i++) {
       A[i] = new int [m];
    }
    return A;
}

__host__ void initialize(int** A, int n, int m, int n_lim, int m_lim)
{
    srand(time(0));
    for(int i = 0; i < n_lim; i++ )
	{
	    for(int j = 0;  j < m_lim;  j++ )
		{
            if(i >= n || j >= m) {
                A[i][j] = 0;
            }
            else {
                A[i][j] = rand()%11 - 2 ;
            	cout.width(3);
            	cout << A[i][j] << "     ";
	    }
		}
    cout << endl;
	}
}

__global__ void block_proiz(int* A, int* B, int* C, int N, int M, int K) 
{
    int bx = blockIdx.x, by = blockIdx.y; 
    int tx = threadIdx.x, ty = threadIdx.y;
    int aBegin = N * RASMER * by;
    int aEnd = aBegin + N - 1;
    int bBegin = RASMER * bx;
    int aStep = RASMER, bStep = RASMER * K;
    int sum = 0;
    
    for ( int ia = aBegin, ib = bBegin; ia <= aEnd; ia += aStep, ib += bStep )
    {
        __shared__ float as [RASMER][RASMER];
        __shared__ float bs [RASMER][RASMER];
        as [ty][tx] = A [ia + N * ty + tx];
        bs [ty][tx] = B [ib + K * ty + tx]; 
        
        __syncthreads ();
        
        for ( int k = 0; k < RASMER; k++ ){
            sum += as [ty][k] * bs [k][tx]; 
        }
        __syncthreads ();
    }
    C [N * RASMER * by + RASMER * bx + K * ty + tx] = sum; 
}

int main()
{
    setlocale(LC_ALL, "Russian");
	int Ax(3), Ay(4), Bx(4), By(3);
	int N = Ax / RASMER;
	if (Ax % RASMER > 0) N++;

	int M = Ay / RASMER;
	if (Ay % RASMER > 0) M++;

	int K = By / RASMER;
	if (By % RASMER > 0) K++;

	int **A = sozdanie(RASMER * N, RASMER * M);
	initialize(A, Ax, Ay, RASMER * N, RASMER * M);
    
	cout << endl;
    
	int **B = sozdanie(RASMER * M, RASMER * K);
	initialize(B, Bx, By, RASMER * M, RASMER * K );

	int **C = sozdanie(RASMER * N, RASMER * K);

	cout << endl << "Matrix C: " << endl << endl;
    
    int size_A = (RASMER * N) * (RASMER * M);
	int size_B = (RASMER * M) * (RASMER * K);
	int size_C = (RASMER * N) * (RASMER * K);
    
    int* host_A = new int [size_A];
	int* host_B = new int [size_B];
	int* host_C = new int [size_C];
    
    for (int i = 0; i < RASMER * N; i++){
		for (int j = 0; j < RASMER * M; j++){
			host_A [i * RASMER * M + j] = A[i][j];
			cout << A[i][j] << " ";
		}
	}
	cout << endl;
	
	for (int i = 0; i < RASMER * M; i++){
		for (int j = 0; j < RASMER * K; j++){
			host_B [i * RASMERr * K + j] = B[i][j];
			cout << B[i][j] << " ";
		}
	}
	cout << endl;
    
    int *gpu_A, *gpu_B, *gpu_C;

    cudaMalloc((void **)&gpu_A,  sizeof(int) * size_A); 
	cudaMalloc((void **)&gpu_B,  sizeof(int) * size_B);
	cudaMalloc((void **)&gpu_C,  sizeof(int) * size_C);

    cudaMemcpy(gpu_A, host_A, sizeof(int) * size_A, cudaMemcpyHostToDevice);
	cudaMemcpy(gpu_B, host_B, sizeof(int) * size_B, cudaMemcpyHostToDevice);

    dim3 gridDim(N, K); 
	dim3 blockDim(RASMER, RASMER);
    
    block_proiz <<< gridDim, blockDim >>> (gpu_A, gpu_B, gpu_C, N, M, K);
	
    cudaMemcpy(host_C, gpu_C, N*sizeof(int), cudaMemcpyDeviceToHost);	
    
    cudaFree (gpu_A);
    cudaFree (gpu_B);
    cudaFree (gpu_C);

	for(int i = 0; i < Ax_number*By_number*N*K; i++) {
		cout << host_C[i] << " ";
	}
	return 0;
}

