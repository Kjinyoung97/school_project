#include <stdio.h>

int main(void)
{
	int A,B;

	printf("x,y�� ���� �Է��ϼ���:");
	scanf("%d%d",&A,&B);

	(A>0 && B>0)? printf("1��и�\n"):printf("");
	(A<0 && B>0)? printf("2��и�\n"):printf("");
	(A<0 && B<0)? printf("3��и�\n"):printf("");
	(A>0 && B<0)? printf("4��и�\n"):printf("");

	return 0;
}