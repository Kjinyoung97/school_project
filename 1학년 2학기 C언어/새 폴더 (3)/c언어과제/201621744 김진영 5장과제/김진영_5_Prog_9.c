#include <stdio.h>

int main (void)
{
	double AC,AE,BC,DE;

	printf("AC,AE,BC�� ���� �Է��Ͻÿ�:\n");
	scanf("%lf%lf%lf",&AC,&AE,&BC);

	DE=AE*BC/AC;

	printf("DE�� ���� %f�Դϴ�.\n",DE);

	return 0;
}