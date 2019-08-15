#include <iostream>
using namespace std;
#include <time.h>
#include <stdlib.h>
#include "sort.h"

const int N = 100000;

void QuickSort(int a[], int l, int r) {
	int i, j, v;
	if (r > l) {
		v = a[r];
		i = l - 1;
		j = r;
		for (; ;) {
			while (a[++i] < v);
			while (a[--j] > v);

			if (i >= j) break;
			swap(a, i, j);
		}
		swap(a, i, r);
		QuickSort(a, l, i - 1);
		QuickSort(a, i + 1, r);
	}
}

int main() {
	int i, a[N + 1];
	double start_time;

	a[0] = -1;
	srand(time(NULL));
	for (i = 1; i <= N; i++) a[i] = rand();

	start_time = clock();
	QuickSort(a, 1, N);
	cout << "퀵 정렬의 실행 시간(N = " << N << ") : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}