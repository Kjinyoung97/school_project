#include <stdio.h>

int main(void)
{
	int i,n,sum,k,ave;
	
	printf("����� ����� ���� ���� ���Ͻðڽ��ϱ�?\n");
	scanf("%d %d",&i, &n);

	sum=0;
	k=i;

	while(i<=n)
	{
		sum+=i;
		i++;
	}

	printf("%d���� %d������ ���� %d�Դϴ�.\n",k,n,sum);
	
	ave=sum/(n-k);
	printf("������ ��հ��� %d�Դϴ�.\n",ave);

	return 0;
}