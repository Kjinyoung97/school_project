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
	
	printf("빛의 속도는 %fkm/s \n", light_speed);
	printf("태양과 지구와의 거리 %fkm \n", distance);
	printf("도달 시간은 %d초\n", time);
	printf("도달 시간은 %d분%d초\n",y,x);

	return 0;
}