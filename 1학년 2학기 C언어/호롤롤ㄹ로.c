//���� ���α׷�
#include <stdio.h>

int main(void)
{
	int year;

	printf("������ �Է��Ͻÿ�: ");
	scanf("%d", &year);

	if ((year%4==0)&&(year%100!=0)||year%400==0)
		printf("������ �½��ϴ�.\n");
	else
		printf("������ �ƴմϴ�.\n");
	
	return 0;
}