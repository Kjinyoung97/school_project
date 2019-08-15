#include<stdio.h>

int main(void)
{
	int grade,n;
	float sum, average;

	n=0;
	sum=0;
	grade=0;
	
	printf("종료하려면 음수를 입력하시오\n");
	printf("성적을 입력하시오: ");


	while(scanf("%d",&grade)!=EOF)
	{
		sum+=grade;
		n++;
	}

	average=sum/n;
	printf("성적의 평균은 %f입니다.\n", average);

	return 0;
}