#include <stdio.h>
int main (void)
{
	int A=1;	//1+3+5+7+9 .. Ȧ��
	int B=0;	//����
	int C=1;	//�ݺ��� Ƚ�� ����

	while(B<500)
	{
		A=A+2;
		B=B+A;	
		C++;
	}
	printf("X���� %d, X�� %d��° ����\n",A,C);

	return 0;
}