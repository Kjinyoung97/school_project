#include <stdio.h>

int main(void)
{
	int A;

	printf("������ �Է��Ͻÿ�:");
	scanf("%d",&A);

	if (A<0)
		A=-A;

	printf("���밪�� %d�Դϴ�.\n",A);

	return 0;
}