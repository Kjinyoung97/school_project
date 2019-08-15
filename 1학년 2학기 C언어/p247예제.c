#include <stdio.h>

int main(void)
{
	int i,n,sum,k,ave;
	
	printf("몇부터 몇까지 더한 값을 구하시겠습니까?\n");
	scanf("%d %d",&i, &n);

	sum=0;
	k=i;

	while(i<=n)
	{
		sum+=i;
		i++;
	}

	printf("%d부터 %d까지의 합은 %d입니다.\n",k,n,sum);
	
	ave=sum/(n-k);
	printf("총합의 평균값은 %d입니다.\n",ave);

	return 0;
}