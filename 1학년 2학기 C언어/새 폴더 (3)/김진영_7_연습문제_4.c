#include<stdio.h>
int main(void)
{
	int m,n,k;
	int A=0;

	printf("m의 값을 입력하시오.(단, m<n)\n");
	scanf("%d",&m);
	printf("n의 값을 입력하시오.\n");
	scanf("%d",&n);

	printf("배수로 할 수를 입력하시오. \n");
	scanf("%d",&k);

	while(n>=m)
	{
		if(n%k==0)
		{
			A=A+n;
		}
		n--;
	}
	printf("m부터 n까지의 %d배수의 합은 %d 입니다.",k,A);
}