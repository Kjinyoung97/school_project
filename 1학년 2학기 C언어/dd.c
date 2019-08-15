#include <stdio.h>
int main (void)
{
	int A;

	printf("정수를 입력하시오:");
	scanf("%d", &A);
	switch(A)
	{
		case 1:
			printf("야호\n");
			break;

	default:
			printf("오잉\n");
	}

		return 0;
}