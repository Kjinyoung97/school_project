#include <stdio.h>

int main(void)
{
	int A,B,C;

	printf("분자를 입력하시오:");
	scanf("%d",&A);

	printf("분모를 입력하시오:");
	scanf("%d",&B);

	if (B==0)
	{
		printf("0으로 나눌 수는 없습니다.\n");
	}
	else
	{
		C=A/B;
		printf("결과는 %d입니다.\n",C);
	}
	
	return 0;
}