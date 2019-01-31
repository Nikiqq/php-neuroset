#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <random>
#include <bitset>
#include <iostream>
#include <ctime>

using namespace std;
const size_t length = 400;
const size_t bytel = length / 8;
using mes_type = std::bitset<length>;

__global__ void computeHash(unsigned char * arr, bool *  finds, int hence)
{
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	finds[index] = false;
	unsigned char local_arr[bytel], second_arr[bytel];
	memcpy(local_arr, arr, length / 8);
	unsigned int nonce = hence + blockIdx.x * blockDim.x + threadIdx.x;
	//printf("nonce - %d\n", nonce);
	memcpy(local_arr + 1, &nonce, sizeof(unsigned int));
	int counter1 = 0;
	//printf("%d\n", sizeof(int));
	for (int i = 0; i < 5; ++i)
	{
		printf("%d\t", local_arr[i]);
	}
	printf("\n");
	short sum = 0;
	for (int j = 0; j < 3; ++j)
	{
		memcpy(second_arr, local_arr, bytel);
		for (int k = 0; k < 16; ++k)
		{
			unsigned char last_el = local_arr[bytel - 1] & 1, bits1 = 0, bits2 = 0;
			for (int i = 0; i < bytel; ++i)
			{
				bits2 = local_arr[i] & 1;
				local_arr[i] >>= 1;
				local_arr[i] |= bits1 << 7;
				bits1 = bits2;
			}
			local_arr[0] |= last_el << 7;
		}

		for (int f = bytel - 1; f >= 0; --f)
		{
		//	printf("%d + %d = ", second_arr[f], local_arr[f]);
			sum = second_arr[f] + local_arr[f] + sum;
			second_arr[f] = sum;
			sum >>= 8;
			sum &= 1;
		//	printf("%d\n", second_arr[f]);
		}
	}
	for (int i = 0; i < bytel; ++i)
	{
		printf("%i\t%d\n", i, second_arr[i]);
	}

	printf("%d\t%d\t", second_arr[bytel - 1], second_arr[0]);
	unsigned char buffer[8]{ second_arr[bytel - 1], second_arr[0]};
	int counter = 2, start = 8;
	for (int i = 0; i < 2; ++i)
	{
		buffer[2 + i * 3] = second_arr[1 + i];
		buffer[3 + i * 3] = second_arr[bytel / 2 + i];
		buffer[4 + i * 3] = second_arr[bytel - 3 + i];
		printf("%d\t%d\t%d\t", second_arr[1 + i], second_arr[bytel / 2 + i], second_arr[bytel - 3 + i]);
	}
	printf("\n");
	unsigned long long int number, remainder = 0;
	memcpy(&number, buffer, 8);

	remainder = number / 4294967296;
	if (remainder == 0) 
		finds[index] = true;
	printf("\n%llu -- %llu \n", number, remainder);
	//printf("%u\n",number);
}

int main()
{
	std::random_device r;
	std::mt19937 gen(r());
	std::bernoulli_distribution d(0.5);

	unsigned long long now = (unsigned long long)time(nullptr);
	const int len = sizeof(__int64) * 8;
	std::bitset<len> timestap( now );
	std::bitset<length> message;
	for (int i = 40; i < len + 40; ++i)
	{
		message[i] = (bool)timestap[i - 40];
	}
	for (int i = len; i < length; ++i)
	{
		message[i] = d( gen );
	}

	std::bitset<8> byte;
	unsigned char * arr = new unsigned char[length / 8], * cuda_message;
	bool some_var = true;
	cout << sizeof(int) << endl;
	for (int i = 0; i < length; i += 8)
	{
		for (int j = 0; j < 8; ++j)
		{
			some_var = (bool)message[j];
			byte[j] = some_var;
		}

		message >>= 8;
		arr[i / 8] = (char)byte.to_ulong();
		//cout << byte << " ";// << (int)(5 + arr[i / 8]) << endl;
		//printf("%u\n", arr[i / 8]);

	}
	unsigned long long int * cuda_key, host_key;

	int size = 256 * 512, hence = pow(16, 6);
	bool *  finds, * host_finds = new bool[size];
	cudaMalloc((void**)&finds, size * sizeof(bool));
	cudaMalloc((void**)&cuda_key, 8);
	cudaMalloc((void**)&cuda_message, length / 8 + 1);
	cudaMemcpy(cuda_message, arr, length / 8 + 1, cudaMemcpyHostToDevice);

	for (int counter = 0; counter < 1; ++counter)
	{
		cout << "epoch " << counter << endl;
		computeHash<<<1, 1 >>>(cuda_message, finds, hence * (counter + 1));
		cudaDeviceSynchronize();
		
		
		//cout << "--------" << endl;
		bool err = cudaMemcpy(host_finds, finds, size * sizeof(bool), cudaMemcpyDeviceToHost);
		for (int i = 0; i < size; ++i)
		{
			if (host_finds[i])
				cout << "thread " << i << " found it" << endl;
		}
	}
	cout << "ended" << endl;
	return 0;
}
