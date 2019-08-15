//윤년 프로그램
#include <stdio.h>

int main(void)
{
	int year;

	printf("연도를 입력하시오: ");
	scanf("%d", &year);

	if ((year%4==0)&&(year%100!=0)||year%400==0)
		printf("윤년이 맞습니다.\n");
	else
		printf("윤년이 아닙니다.\n");
	
	return 0;
}