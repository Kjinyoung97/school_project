#include <stdio.h>
int main(void)
{
	int A=100;
	int B=0;

	while(A>=1)
	{
		if(A%7==0)
		{
			B=B+A;
		}
		A--;
	}

	printf("1���� 100������ 7�� ��� ����: %d\n",B);
}