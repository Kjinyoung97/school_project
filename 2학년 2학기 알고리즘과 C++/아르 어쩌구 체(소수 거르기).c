#include <stdio.h>
#pragma comment(lib,"dsound.lib")

#define Size 258

int n,i,k,l;
int Num[Size];

int main(void) {

	Sca();

	for (; (n < 0 || n > 258) ;) {
		printf("�ٽ� �Է��Ͻÿ�\n");
		Sca();
	}
	printf("�Է��� ���� %d �Դϴ�\n", n);
	printf("�Է��� ���� �����մϴ�.\n");
	Num[0] = 0;


	for (i = 1; i <= n; i++) {
		Num[i] = i;
		printf("%d \t", Num[i]);
		if (n / 10 == 0) printf("\n");
	}

	printf("\n�Ҽ��� �ƴ� 1�� �����մϴ�\n���ŵ� ���ڴ� 0���� ǥ�� �˴ϴ�.\n");
	Num[1] = 0;


	for (k = 2; k <= n; k++) {
		Pri(k);
		printf("\n");
		printf("%d�� ����� ����\n", k);
	}
	
	
	return 0;
}

int Sca(void) {

	printf("�Ҽ��� üũ�� ������ �Է��Ͻÿ�. �ִ밪�� 258 �Դϴ� \n");
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