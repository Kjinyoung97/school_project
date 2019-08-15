#include <stdio.h>

int main(void)
{
	int A;

	printf("정수를 입력하시오:");
	scanf("%d",&A);

	if (A<0)
		A=-A;

	printf("절대값은 %d입니다.\n",A);

	return 0;
}