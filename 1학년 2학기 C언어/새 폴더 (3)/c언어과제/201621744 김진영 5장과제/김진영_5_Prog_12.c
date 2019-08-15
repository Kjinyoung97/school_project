#include <stdio.h>

int main (void)
{
	char A;
	unsigned int B=0x00000000;

	printf("문자를 입력하시오:");
	scanf("%c",&A);
	B=B|A;
	getchar();

	printf("문자를 입력하시오:");
	scanf("%c",&A);
	B=B<<8;
	B=B|A;
	getchar();

	printf("문자를 입력하시오:");
	scanf("%c",&A);
	B=B<<8;
	B=B|A;
	getchar();

	printf("문자를 입력하시오:");
	scanf("%c",&A);
	B=B<<8;
	B=B|A;
	getchar();

	printf("결과값:%08x",B);

	return 0;
}