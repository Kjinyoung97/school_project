#include <stdio.h>

int main (void)
{
	int A,B;

	printf("정수를 입력하시오:\n");
	scanf("%d",&A);

	B=~A+1;

	printf("2의 보수:%d\n",B);

	return 0;
}