#include <stdio.h>
int main(void)
{
	int A=0; 
	int B=0;

	A=100;

	while(A>=1)
	{
		if(A%2==0)
		{
			B=B+A;
		}
	A--;
	}

	printf("Â¦¼ö °ªÀÇ ÃÑ ÇÕ°è: %d\n",B);
}