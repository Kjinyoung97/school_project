#include <stdio.h>

int main(void)
{
	float A,B,C,D,E; //중간,기말,출석,레포트,합산 점수

	printf("중간고사 점수, 기말고사 점수, 출석 점수, 레포트 점수를 순서대로 입력하시오.\n");
	scanf("%f %f %f %f", &A, &B, &C, &D);

	E=A+B+C+D;

	if (A>30||B>30||C>10||D>20)
	{
		printf("잘못된 값입니다.");
	}
	else
	{
		if (E>=95)
			printf("학점은 A+입니다.\n");
		else if (E>=90)
			printf("학점은 A입니다.\n");
		else if(E>=85)
			printf("학점은 B+입니다.\n");
		else if(E>=80)
			printf("학점은 B입니다.\n");
		else if(E>=75)
			printf("학점은 C+입니다.\n");
		else if(E>=70)
			printf("학점은 C입니다.\n");
		else if(E>=65)
			printf("학점은 D+입니다.\n");
		else if(E>=60)
			printf("학점은 C입니다.\n");
		else
			printf("학점은 F입니다.\n");

		printf("입력된 점수는\n 중간고사: %f점\n 기말고사: %f점\n 출석:%f점\n 과제물:%f점\n 총점:%f 입니다.",A,B,C,D,E);
	}
	return 0;
}