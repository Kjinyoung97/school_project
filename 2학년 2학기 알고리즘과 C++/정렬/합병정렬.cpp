#include <iostream>
using namespace std;
#include <time.h>
#include <stdlib.h>
#include "sort.h"

const int N = 100000;
int b[N + 1];

void MergeSort(int a[], int l, int r) {
	int i, j, k, m;
	if (r > l) {
		m = (r + l) / 2;
		MergeSort(a, l, m);
		MergeSort(a, m + 1, r);
		for (i = m + 1; i > l; i--) b[i - 1] = a[i - 1];
		for (j = m; j < r; j++) b[r + m - j] = a[j + 1];
		for (k = l; k <= r; k++)
			a[k] = (b[i] < b[j]) ? b[i++] : b[j--];
	}
}

int main() {
	int i, a[N + 1];
	double start_time;

	srand(time(NULL));
	for (i = 1; i < N; i++) a[i] = rand();

	start_time = clock();
	MergeSort(a, 1, N);
	cout << "합병 정렬의 실행 시간(N = " << N << " ) : " <<
		clock() - start_time << endl;
	CheckSort(a, N);
}