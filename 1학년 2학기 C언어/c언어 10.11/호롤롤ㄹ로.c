//���� ���α׷�
#include <stdio.h>

int main(void)
{
	int year, result;

	printf("������ �Է��Ͻÿ�: ");
	scanf("%d", &year);

	result=((year%4==0)&&(year%100!=0))||(year%400==0);
	
	if (result=1)
		printf("������ �ƴմϴ�.\n");
	else
		printf("������ �½��ϴ�.\n");
	
	return 0;
}