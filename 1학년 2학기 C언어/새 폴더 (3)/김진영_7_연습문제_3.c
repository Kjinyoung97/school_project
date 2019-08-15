#include <stdio.h>
int main(void)
{
	int A=100;
	int B=0;

	while(A>=1)
	{
		if(A%7==0)
		{
			B=B+A;
		}
		A--;
	}

	printf("1부터 100까지의 7의 배수 총합: %d\n",B);
}