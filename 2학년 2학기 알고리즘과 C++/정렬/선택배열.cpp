#include <iostream>
using namespace std;
#include <time.h>
#include <stdlib.h>
#include "sort.h"

const int N = 10000;
void SelectionSort(int a[], int N) {
	int i, j, min;
	for (i = 1; i < N; i++) {
		min = i;
		for (j = i + 1; j <= N; j++)
			if (a[j] < a[min]) min = j;
		swap(a, min, i);
	}
}

int main() {
	int i, a[N + 1];
	double start_time;

	srand(time(NULL));
	for (i = 1; i <= N; i++) a[i] = rand();

	start_time = clock();
	SelectionSort(a, N);
	cout << "선택 정렬의 실행 시간 (N = " << N << ") : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}