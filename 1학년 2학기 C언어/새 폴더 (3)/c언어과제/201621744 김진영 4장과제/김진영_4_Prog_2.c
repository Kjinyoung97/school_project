#include <stdio.h>

int main(void)
{
	int A;

	printf("16진수 정수를 입력하시오.\n");
	scanf("%x",&A);
	printf("8진수로는 %#o입니다.\n",A);
	printf("10진수로는 %d입니다.\n",A);
	printf("16진수로는 %#x입니다.\n",A);
	
	return 0;
}