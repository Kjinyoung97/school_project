#include <stdio.h>

int main(void)
{
	const double SQMETER_PER_PYEONG=3.3058;
	int x;
	y;

	printf("평을 입력하세요.\n");
	scanf("%d",&x);
	y=SQMETER_PER_PYEONG*x;
	printf("%lf평방미터입니다.\n",y);

	return 0;
}