#include <stdio.h>

int main(void)
{
	float x,y,z,sum,avg;

	printf("첫 번째 실수를 입력하시오: ");
	scanf("%f",&x);

	printf("두 번째 실수를 입력하시오: ");
	scanf("%f",&y);

	printf("세 번째 실수를 입력하시오: ");
	scanf("%f",&z);

	sum=x+y+z;
	avg=sum/3.0;

	printf("세 실수의 합은 %f이다.\n세 실수의 평균은 %f이다",sum,avg);

	return 0;
}