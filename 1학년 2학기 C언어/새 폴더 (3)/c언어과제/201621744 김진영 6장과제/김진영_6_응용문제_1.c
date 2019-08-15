#include <stdio.h>

int main(void)
{
	int M;
	int C_500, C_100, C_50, C_10;
	int R;

	printf("남은 잔돈을 입력하시오. 단 잔돈은 1000원이하만 가능: ");
	scanf("%d",&M);

	if (M<1000)
	{
		C_500=M/500;
		R=M%500;

		C_100=R/100;
		R=R%100;

		C_50=R/50;
		R=R%50;

		C_10=R/10;
		
		printf("입력한 잔돈은 %d원입니다.\n",M);
		printf("500원 짜리 동전 %d 개가 반환됩니다.\n",C_500);
		printf("100원 짜리 동전 %d 개가 반환됩니다.\n",C_100);
		printf("50원 짜리 동전 %d 개가 반환됩니다.\n", C_50);
		printf("10원 짜리 동전 %d 개가 반환됩니다.\n", C_10);
	}
	else
	{
		printf("반환 불가. 범위 내 액수를 입력하시오.\n");
	}
	
	return 0;
}