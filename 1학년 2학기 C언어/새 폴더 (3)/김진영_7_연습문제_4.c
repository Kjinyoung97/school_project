#include<stdio.h>
int main(void)
{
	int m,n,k;
	int A=0;

	printf("m�� ���� �Է��Ͻÿ�.(��, m<n)\n");
	scanf("%d",&m);
	printf("n�� ���� �Է��Ͻÿ�.\n");
	scanf("%d",&n);

	printf("����� �� ���� �Է��Ͻÿ�. \n");
	scanf("%d",&k);

	while(n>=m)
	{
		if(n%k==0)
		{
			A=A+n;
		}
		n--;
	}
	printf("m���� n������ %d����� ���� %d �Դϴ�.",k,A);
}