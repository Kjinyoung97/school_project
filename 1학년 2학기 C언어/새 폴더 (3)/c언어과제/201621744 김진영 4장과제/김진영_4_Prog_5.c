#include <stdio.h>

int main(void)
{
	const double SQMETER_PER_PYEONG=3.3058;
	int x;
	y;

	printf("���� �Է��ϼ���.\n");
	scanf("%d",&x);
	y=SQMETER_PER_PYEONG*x;
	printf("%lf�������Դϴ�.\n",y);

	return 0;
}