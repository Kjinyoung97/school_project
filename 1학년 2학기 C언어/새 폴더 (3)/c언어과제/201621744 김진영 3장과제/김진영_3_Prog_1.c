#include <stdio.h>

int main(void)
{
	float x,y,z,sum,avg;

	printf("ù ��° �Ǽ��� �Է��Ͻÿ�: ");
	scanf("%f",&x);

	printf("�� ��° �Ǽ��� �Է��Ͻÿ�: ");
	scanf("%f",&y);

	printf("�� ��° �Ǽ��� �Է��Ͻÿ�: ");
	scanf("%f",&z);

	sum=x+y+z;
	avg=sum/3.0;

	printf("�� �Ǽ��� ���� %f�̴�.\n�� �Ǽ��� ����� %f�̴�",sum,avg);

	return 0;
}