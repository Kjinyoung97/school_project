#include <stdio.h>

int main(void)
{
	float base,height,area;

	printf("삼각형의 밑변을 입력하시오: ");
	scanf("%f",&base);

	printf("삼각형의 높이를 입력하시오: ");
	scanf("%f", &height);

	area=0.5*height*base;
	printf("삼각형의 넓이:%f \n",area);

	return 0;
}