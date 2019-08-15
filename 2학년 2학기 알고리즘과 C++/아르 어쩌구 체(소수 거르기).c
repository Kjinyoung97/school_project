#include <stdio.h>
#pragma comment(lib,"dsound.lib")

#define Size 258

int n,i,k,l;
int Num[Size];

int main(void) {

	Sca();

	for (; (n < 0 || n > 258) ;) {
		printf("다시 입력하시오\n");
		Sca();
	}
	printf("입력한 값은 %d 입니다\n", n);
	printf("입력한 값을 나열합니다.\n");
	Num[0] = 0;


	for (i = 1; i <= n; i++) {
		Num[i] = i;
		printf("%d \t", Num[i]);
		if (n / 10 == 0) printf("\n");
	}

	printf("\n소수가 아닌 1을 제거합니다\n제거된 숫자는 0으로 표시 됩니다.\n");
	Num[1] = 0;


	for (k = 2; k <= n; k++) {
		Pri(k);
		printf("\n");
		printf("%d의 배수를 제거\n", k);
	}
	
	
	return 0;
}

int Sca(void) {

	printf("소수를 체크할 정수를 입력하시오. 최대값은 258 입니다 \n");
	scanf_s("%d", &n);

	return n;
}

int Pri(int k) {

	l = 1;

	do {
		if ((Num[l] % k == 0) && (Num[l] / k >= 2)) {
			Num[l] = 0;
		}
		printf("%d \t", Num[l]);
		if (n / 10 == 0) printf("\n");
		l++;
	} while (l <= n);

	return 0;
}