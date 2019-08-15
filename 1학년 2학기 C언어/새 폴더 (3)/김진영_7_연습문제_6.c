#include <stdio.h>
#include <math.h>
int main(void)
{
	double A=1;
	double B=1;
	double sum;
	
	sum=pow(1.0,1.0);

	while(A<=19)
	{
		A=A+2;
		B=B+1;
		sum=sum+pow(A,B);
	}
	 printf("값은 %lf이다.",sum);
}