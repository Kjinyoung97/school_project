#include <stdio.h>

int main(void)
{
	float base,height,area;

	printf("�ﰢ���� �غ��� �Է��Ͻÿ�: ");
	scanf("%f",&base);

	printf("�ﰢ���� ���̸� �Է��Ͻÿ�: ");
	scanf("%f", &height);

	area=0.5*height*base;
	printf("�ﰢ���� ����:%f \n",area);

	return 0;
}