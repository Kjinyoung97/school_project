#include <stdio.h>

int main(void)
{
	int A,B,C;

	printf("���ڸ� �Է��Ͻÿ�:");
	scanf("%d",&A);

	printf("�и� �Է��Ͻÿ�:");
	scanf("%d",&B);

	if (B==0)
	{
		printf("0���� ���� ���� �����ϴ�.\n");
	}
	else
	{
		C=A/B;
		printf("����� %d�Դϴ�.\n",C);
	}
	
	return 0;
}