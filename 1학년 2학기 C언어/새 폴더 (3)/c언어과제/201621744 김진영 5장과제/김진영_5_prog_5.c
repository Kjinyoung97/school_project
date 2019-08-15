#include <stdio.h>

int main(void)
{
	int A,B,C;

	printf("정수를 입력하시오:\n");
	scanf("%d",&A);

	B=A/10;
	C=A%10;

	printf("십의자리:%d\n",B);
	printf("일의자리:%d\n",C);

	return 0;
}