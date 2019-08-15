#include <stdio.h>

int main(void)
{
	int A;

	printf("양의 정수를 입력 받아 짝수일 경우 2로 나누고, 홀수일 경우 3배 한후 1을 더하는 프로그램\n");
	printf("양의 정수를 입력하시오: ");

	scanf("%d",&A);

	if (A>0)
	{
		if(A%2==0)
		{
			printf("결과값: %d\n",A/2);
		}
		else
		{
			printf("결과값:%d\n",A*3+1);
		}
	}
	else
	{
		printf("양의 정수를 입력하시오.\n");
	}
	return 0;
}