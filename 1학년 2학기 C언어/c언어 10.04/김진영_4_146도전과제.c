#include <stdio.h>
int main(void)
{
	double light_speed=300000;
	double distance=149600000;
	int x;
	int y;
	int time;
	
	time=distance/light_speed;
	y = time / 60;
	x= time%60;
	
	printf("���� �ӵ��� %fkm/s \n", light_speed);
	printf("�¾�� �������� �Ÿ� %fkm \n", distance);
	printf("���� �ð��� %d��\n", time);
	printf("���� �ð��� %d��%d��\n",y,x);

	return 0;
}