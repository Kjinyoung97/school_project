#include <stdio.h>

int main (void)
{
	int A;

	printf("정수를 입력하시오:");
	scanf("%d",&A);

	if (A%2==0)
		printf("입력된 정수는 짝수입니다.\n");
	else
		printf("입력된 정수는 홀수입니다.\n");
	
	return 0;
}