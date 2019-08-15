#include<stdio.h>
int inc(int counter);

int main (void)
{
	int i=10;

	printf("함수 호출 전 i=%d\n",i);
	inc (i);
	printf("함수 호출 후 i=%d\n", i);

	return 0;
}

int inc (int counter)
{
	while (counter<=15)
	{
		printf("counter 값: %d\n",counter);
		counter=counter+1;
	}
	return counter;
}