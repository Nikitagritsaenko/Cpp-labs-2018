#include <iostream>
#include <crtdbg.h>
#include <time.h>
#include <assert.h>
#include <windows.h>
#include "bin_search_tree.h"
#pragma warning(disable : 4996)
using namespace std;

#define DATA_SIZE_MIN 100000
#define DATA_SIZE_MAX 1000000
#define SIZE_STEP 100000

typedef struct
{
	LARGE_INTEGER t0, t1;
	LARGE_INTEGER frequency;
} timer_t;

int Random(int a, int b)
{
	double x, xd;
	x = rand();
	xd = (x * (b - a)) / (RAND_MAX + 1) + a;
	return (int)xd;
}

void FillArray(FILE* in, int data[], int size)
{
	for (int i = 0; i < size; i++)
		fread(&(data[i]), sizeof(int), 1, in);
}

void FillArrayMonotone(int data[], int size)
{
	for (int i = 0; i < size; i++)
		data[i] = i*100;
}

void PrintResult(double const arr[], int size)
{
	int i = 0, step = DATA_SIZE_MIN;
	for (i = 0; i < size; i++)
	{
		printf("%lf\n", arr[i]);
		step += SIZE_STEP;
	}
	printf("\n");
}

void TimerCreate(timer_t* self)
{
	assert(self);
	QueryPerformanceFrequency(&self->frequency);
	QueryPerformanceCounter(&self->t1);
	self->t0 = self->t1;
}

double TimerTick(timer_t* self)
{
	assert(self);
	self->t0 = self->t1;
	QueryPerformanceCounter(&self->t1);
	return 1000.0 * (double)(self->t1.QuadPart - self->t0.QuadPart) / (double)self->frequency.QuadPart;
}

bool* Sieve(int n)
{
	bool* S = new bool[n + 1];
	S[1] = 0;
	for (int k = 2; k <= n; k++)
		S[k] = 1;

	for (int k = 2; k*k <= n; k++)
	{
		if (S[k] == 1)
		{
			for (int l = k * k; l <= n; l += k)
				S[l] = 0;
		}
	}
	return S;
}

int GeneratePrime(int max)
{
	bool *isPrime = Sieve(max);
	int i = 0;
	for (i = max; i >= 2; i--)
	{
		if (isPrime[i] == true)
			break;
	}
	delete[] isPrime;
	return i;
}

typedef struct UniversalHash
{
	int p;
	int a, b;
	int m;
} u_hash_t;

int Hash(int key)
{
	//метод середины квадрата
	key *= key;
	key >>= 11; // Отбрасываем 11 младших бит
	return key % 65536; // Возвращаем 16 младших бит
}

u_hash_t InitHash(int size)
{
	u_hash_t h;
	h.m = size;
	srand((unsigned)time(NULL));
	h.p = GeneratePrime(Random(size, size * 2));
	h.a = Random(1, h.p - 1);
	h.b = Random(0, h.p - 1);
	return h;
}

u_hash_t h;

int UniHash(int key)
{
	return ((h.a * key + h.b) % h.p) % h.m;
}

double TimeMeasurement(BST &t, int data[], int size)
{
	timer_t timer;
	int i = 0, j = 0;
	double dt = 0.0;
	bin_tree_t *node = NULL;
	for (i = size; i <= size + SIZE_STEP; i++)
		t.Add(data[i]);
	srand((unsigned)time(NULL));
	TimerCreate(&timer);
	dt = TimerTick(&timer);
	for (j = 1; j < 10000; j++)
	{
		int r = data[Random(DATA_SIZE_MIN, size+SIZE_STEP)];
		t.Search(r, &node);
	}
	dt = TimerTick(&timer);
	dt /= 10000;
	return dt;
}

void AsymptoticsResearch(int data[])
{
	int i = 0, size = 0;
	int stepCount = (DATA_SIZE_MAX - DATA_SIZE_MIN) / SIZE_STEP + 1;
	double *resNoHash = new double[stepCount];
	double *resHash = new double[stepCount];
	double *resUniHash = new double[stepCount];
	int(*ptr1)(int) = &Eq;
	int(*ptr2)(int) = &Hash;
	int(*ptr3)(int) = &UniHash;
	BST t1(ptr1); BST t2(ptr2); BST t3(ptr3);
	srand((unsigned)time(NULL));
	h = InitHash(DATA_SIZE_MIN);

	for (size = DATA_SIZE_MIN; size < DATA_SIZE_MAX; size += SIZE_STEP)
	{
		resNoHash[i] = TimeMeasurement(t1, data, size);
		resHash[i] = TimeMeasurement(t2, data, size);
		resUniHash[i] = TimeMeasurement(t3, data, size);
		i++;
	}

	printf("Search time without hashing\n");
	PrintResult(resNoHash, i);
	printf("Search time with hashing\n");
	PrintResult(resHash, i);
	printf("Search time with universal hashing\n");
	PrintResult(resUniHash, i);

	delete[] resNoHash;
	delete[] resHash;
	delete[] resUniHash;
	t1.Free();
	t2.Free();
	t3.Free();
}


int main(void)
{
	// 0. Init data
	int* data = new int[DATA_SIZE_MAX];
	int* res = new int[DATA_SIZE_MAX];
	FILE *in = fopen("rand.bin", "rb");
	FillArray(in, data, DATA_SIZE_MAX);
	for (int i = 1; i < DATA_SIZE_MAX; i++)
		res[i] = Hash(data[i]);
	//FillArrayMonotone(data, DATA_SIZE_MAX);
	fclose(in);

	// 1. Research
	AsymptoticsResearch(data);
	free(data);
	system("pause");
	_CrtDumpMemoryLeaks();
	return 0;
}