#include <stdio.h>

int main(void)
{
	double w,h,area,perimeter;

	printf("사각형의 세로를 입력하시오: ");
	scanf("%lf", &h);

	printf("사각형의 가로를 입력하시오: ");
	scanf("%lf", &w);

	area=w*h;
	perimeter=2*(w+h);

	printf("사각형의 넓이: %lf\n사각형의 둘레: %lf\n",area,perimeter);

	return 0;
}