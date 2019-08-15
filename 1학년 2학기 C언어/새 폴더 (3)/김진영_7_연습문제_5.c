#include <stdio.h>
int main (void)
{
	int A=1;	//1+3+5+7+9 .. 홀수
	int B=0;	//조건
	int C=1;	//반복문 횟수 세기

	while(B<500)
	{
		A=A+2;
		B=B+A;	
		C++;
	}
	printf("X값은 %d, X는 %d번째 숫자\n",A,C);

	return 0;
}