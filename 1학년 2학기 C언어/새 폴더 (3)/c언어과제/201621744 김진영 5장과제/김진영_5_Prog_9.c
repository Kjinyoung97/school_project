#include <stdio.h>

int main (void)
{
	double AC,AE,BC,DE;

	printf("AC,AE,BC의 값을 입력하시오:\n");
	scanf("%lf%lf%lf",&AC,&AE,&BC);

	DE=AE*BC/AC;

	printf("DE의 값은 %f입니다.\n",DE);

	return 0;
}