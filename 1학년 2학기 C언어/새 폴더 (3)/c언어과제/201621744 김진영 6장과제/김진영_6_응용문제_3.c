#include <stdio.h>

int main(void)
{
	int A,B,C,D,F;

	printf("3���� ������ ������� �Է�: \n");
	scanf("%d %d %d", &A, &B, &C);

	D=A-B;
	F=B-C;

	if(D<0)
	{
		printf("ù ��° ������ ���� ��: %d\n", -D);
	}
	else
		printf("ù ��° ������ ���� ��: %d\n", D);
	if (F<0)
	{
		printf("�� ��° ������ ���� ��: %d\n", -F);
	}
	else
		printf("�� ��° ������ ���� ��: %d\n", F);

	return 0;
}