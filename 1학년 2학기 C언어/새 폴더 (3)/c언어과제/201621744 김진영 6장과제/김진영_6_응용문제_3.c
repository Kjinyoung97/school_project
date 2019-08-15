#include <stdio.h>

int main(void)
{
	int A,B,C,D,F;

	printf("3개의 정수를 순서대로 입력: \n");
	scanf("%d %d %d", &A, &B, &C);

	D=A-B;
	F=B-C;

	if(D<0)
	{
		printf("첫 번째 인접한 수의 차: %d\n", -D);
	}
	else
		printf("첫 번째 인접한 수의 차: %d\n", D);
	if (F<0)
	{
		printf("두 번째 인접한 수의 차: %d\n", -F);
	}
	else
		printf("두 번째 인접한 수의 차: %d\n", F);

	return 0;
}