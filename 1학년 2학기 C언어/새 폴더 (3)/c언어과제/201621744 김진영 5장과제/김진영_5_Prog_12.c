#include <stdio.h>

int main (void)
{
	char A;
	unsigned int B=0x00000000;

	printf("���ڸ� �Է��Ͻÿ�:");
	scanf("%c",&A);
	B=B|A;
	getchar();

	printf("���ڸ� �Է��Ͻÿ�:");
	scanf("%c",&A);
	B=B<<8;
	B=B|A;
	getchar();

	printf("���ڸ� �Է��Ͻÿ�:");
	scanf("%c",&A);
	B=B<<8;
	B=B|A;
	getchar();

	printf("���ڸ� �Է��Ͻÿ�:");
	scanf("%c",&A);
	B=B<<8;
	B=B|A;
	getchar();

	printf("�����:%08x",B);

	return 0;
}