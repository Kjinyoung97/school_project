#include<stdio.h>

int main(void)
{
	int grade,n;
	float sum, average;

	n=0;
	sum=0;
	grade=0;
	
	printf("�����Ϸ��� ������ �Է��Ͻÿ�\n");
	printf("������ �Է��Ͻÿ�: ");


	while(scanf("%d",&grade)!=EOF)
	{
		sum+=grade;
		n++;
	}

	average=sum/n;
	printf("������ ����� %f�Դϴ�.\n", average);

	return 0;
}