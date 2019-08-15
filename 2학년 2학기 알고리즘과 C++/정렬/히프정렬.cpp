#include <iostream>
using namespace std;
#include <time.h>
#include <stdlib.h>
#include "sort.h"

const int N = 100000;

void heapify(int a[], int h, int m) {
	int j, v;
	v = a[h];
	for (j = 2 * h; j <= m; j *= 2) {
		if (j < m && a[j] < a[j + 1]) j++;
		if (v >= a[j]) break;
		else a[j / 2] = a[j];
	}
	a[j / 2] = v;
}

void HeapSort(int a[], int n) {
	int i;
	for (i = n / 2; i >= 1; i--)
		heapify(a, i, n);
	for (i = n - 1; i >= 1; i--) {
		swap(a, 1, i + 1);
		heapify(a, 1, i);
	}
}

int main() {
	int i, a[N + 1];
	double start_time;

	srand(time(NULL));
	for (i = 1; i <= N; i++) a[i] = rand();

	start_time = clock();
	HeapSort(a, N);
	cout << "히프 정렬의 실행 시간 ( N = " << N << " ) : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}