#include <stdio.h>

int main(void)
{
	int A;

	printf("성적을 입력하시오:");
	scanf("%d",&A);

	if (A>=95)
		printf("학점A+\n");
	else if (A>=90)
		printf("학점A\n");
	else if (A>=85)
		printf("학점B+\n");
	else if (A>=80)
		printf("학점B\n");
	else if (A>=75)
		printf("학점C+\n");
	else if (A>=70)
		printf("학점C\n");
	else if (A>=65)
		printf("학점D+\n");
	else if (A>=60)
		printf("학점D\n");
	else
		printf("학점F\n");

	return 0;
}