#include <stdio.h>

int main(void)
{
	int A;

	printf("���� ������ �Է� �޾� ¦���� ��� 2�� ������, Ȧ���� ��� 3�� ���� 1�� ���ϴ� ���α׷�\n");
	printf("���� ������ �Է��Ͻÿ�: ");

	scanf("%d",&A);

	if (A>0)
	{
		if(A%2==0)
		{
			printf("�����: %d\n",A/2);
		}
		else
		{
			printf("�����:%d\n",A*3+1);
		}
	}
	else
	{
		printf("���� ������ �Է��Ͻÿ�.\n");
	}
	return 0;
}