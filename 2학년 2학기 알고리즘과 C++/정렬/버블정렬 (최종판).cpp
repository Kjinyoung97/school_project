#include <iostream>
using namespace std;
#include <time.h>
#include <stdlib.h>
#include "sort.h"

const int N = 10000;

void ImpBubbleSort(int a[], int N) {
	for (int u = N-1; u > 0; u--) {
		for (int j = N-1; j > 0; j--)
			if (a[j - 1] > a[j]) {
				swap(a[j], a[j - 1]);
			}
	}
}

int main() {
	int i, a[N + 1];
	double start_time;

	srand(time(NULL));
	for (i = 0; i < N-1; i++) a[i] = rand();
	start_time = clock();
	ImpBubbleSort(a, N);
	cout << "버블 정렬의 실행 시간 (N=" << N << ") : " <<
		clock() - start_time << endl;
	CheckSort(a, N-1);
}