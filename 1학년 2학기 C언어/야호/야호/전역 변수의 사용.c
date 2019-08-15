#include <stdio.h>
void f(void);

int main(void)
{
	int i;
	for(i=0;i<5;i++)
	{
		printf("i");
		f();
	}
	return 0;
}

void f(void)
{
	int i;
	for (i=0;i<10;i++)
	{
		printf("#");
		printf("i");
	}
	printf("\n");
}