#include <stdio.h>

int main(void)
{
	double w,h,area,perimeter;

	printf("�簢���� ���θ� �Է��Ͻÿ�: ");
	scanf("%lf", &h);

	printf("�簢���� ���θ� �Է��Ͻÿ�: ");
	scanf("%lf", &w);

	area=w*h;
	perimeter=2*(w+h);

	printf("�簢���� ����: %lf\n�簢���� �ѷ�: %lf\n",area,perimeter);

	return 0;
}