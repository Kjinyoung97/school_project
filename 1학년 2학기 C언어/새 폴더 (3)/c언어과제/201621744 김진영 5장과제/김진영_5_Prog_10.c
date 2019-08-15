#include <stdio.h>

int main(void)
{
	int A,B;

	printf("x,y의 값을 입력하세요:");
	scanf("%d%d",&A,&B);

	(A>0 && B>0)? printf("1사분면\n"):printf("");
	(A<0 && B>0)? printf("2사분면\n"):printf("");
	(A<0 && B<0)? printf("3사분면\n"):printf("");
	(A>0 && B<0)? printf("4사분면\n"):printf("");

	return 0;
}