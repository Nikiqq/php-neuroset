#include <conio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"


__global__ void calculate(const char *input, char *output)
{
    char *s = '0';
    strcat(input, s);
    strcat(output, input);
}

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	string prevBlock = "000000cdccf49f13f5c3f14a2c12a56ae60e900c5e65bfe1cc24f038f0668a6c";
	string timestamp = "01/01/2017";
	int nonce = 0;
	
	string init = prevBlock + timestamp;
	char * data_in = new char[init.length() + 1];
	strcpy(data_in, init.c_str());

	char * data_out = new char[init.length() + 2];

	char *data_in_gpu;
	char *data_out_gpu;

	cudaMalloc((void **)&data_in_gpu, sizeof(char) * init.length() + 1);
	cudaMalloc((void **)&data_out_gpu, sizeof(char) * init.length() + 2);

	cudaMemcpy(data_in_gpu, data_in, sizeof(char) * init.length() + 1, cudaMemcpyHostToDevice);

	dim3 gridDim(1);
	dim3 blockDim(1);

	calculate < << gridDim, blockDim >> >(data_in_gpu, data_out_gpu);

	cudaMemcpy(data_out, data_out_gpu, sizeof(char) * init.length() + 2, cudaMemcpyDeviceToHost);

	for (int i = 0; i < init.length() + 2; i++) {
		cout << data_out[i];
	}

	cudaFree(data_in_gpu);
	cudaFree(data_out_gpu);
	

	delete data_in;
	delete data_out;

	_getch(); // 
	return 0;
}